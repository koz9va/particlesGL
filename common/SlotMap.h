//
// Created by koz9va on 11.10.20.
//

#ifndef GL_SLOTMAP_H
#define GL_SLOTMAP_H
#include <cstdint>
#include <vector>

//type must be a struct that contains uint64_t id
template<typename object>
class SlotMap {
private:
	const size_t chunk_size = 256;
	std::vector<object*> object_table;
	std::vector<int> free_list;
public:
	int amount = 0;

	int64_t create_object() {
		int i, free;
		object *chunk;
		if(free_list.empty()) {
			chunk = new object[chunk_size];
			for(i = chunk_size - 1; i >= 0; --i) {
				chunk[i].id = object_table.size() * chunk_size + i;
				free_list.push_back(object_table.size() * chunk_size + i);
			}
			object_table.push_back(chunk);
		}
		free = free_list.back();
		free_list.pop_back();
		++amount;
		return object_table[free / chunk_size][free % chunk_size].id;
	}

	object *get_object(int64_t id) {
		object *obj;
		obj = object_table[(id & 0xFFFFFFFF) / chunk_size] + ((id & 0xFFFFFFFF) % chunk_size);
		return obj->id != id ? nullptr : obj;
	}

	void destroy_object(int64_t id) {
		object *obj;
		obj = get_object(id);
		obj->id = (obj->id & 0xFFFFFFFF) | (((obj->id >> 32) + 1) << 32);
		free_list.push_back(id & 0xFFFFFFFF);
		if(amount < 1)
			--amount;
	}
};



#endif //GL_SLOTMAP_H
