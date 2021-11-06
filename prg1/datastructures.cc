// Datastructures.cc

#include "datastructures.hh"

#include <random>

#include <cmath>


std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{





}

Datastructures::~Datastructures()
{




}

int Datastructures::place_count()
{


    return places_data_.size();
}

void Datastructures::clear_all()
{

    places_data_.clear();
    areas_data_.clear();
    sorted_by_name_.clear();
    sorted_by_coord_.clear();
}

std::vector<PlaceID> Datastructures::all_places()
{

    std::vector<PlaceID> all_place_ids;
    for(std::unordered_map<long long int, place_info>::iterator it = places_data_.begin(); it != places_data_.end(); ++it)
    {
        all_place_ids.push_back(it->first);
    }

    return all_place_ids;
}

bool Datastructures::add_place(PlaceID id, const Name& name, PlaceType type, Coord xy)
{
    if(places_data_.find(id) != places_data_.end())
    {
        return false;
    }
    places_data_.insert({id,{name,type,Coord(xy)}});
    sorted_by_name_.insert({name,id});
    sorted_by_coord_.insert({xy,id});
    return true;
}

std::pair<Name, PlaceType> Datastructures::get_place_name_type(PlaceID id)
{

    std::pair<Name,PlaceType> name_and_type;
    for(std::unordered_map<long long int, place_info>::iterator it = places_data_.begin(); it != places_data_.end(); ++it)
    {
        if(it->first == id)
        {
            name_and_type = std::make_pair(it->second.place_name_,it->second.place_type_);
            return name_and_type;
        }
    }
    return {NO_NAME, PlaceType::NO_TYPE};
}

Coord Datastructures::get_place_coord(PlaceID id)
{

    for(std::unordered_map<long long int, place_info>::iterator it = places_data_.begin(); it != places_data_.end(); ++it)
    {
        if(it->first == id)
        {

            return it->second.cordinates_;
        }
    }
    return NO_COORD;
}

bool Datastructures::add_area(AreaID id, const Name &name, std::vector<Coord> coords)
{


    if(areas_data_.find(id) == areas_data_.end())
    {
        areas_data_[id] = {name,coords,-1};
        return true;
    }
    return false;
}

Name Datastructures::get_area_name(AreaID id)
{

    auto it = areas_data_.find(id);
    if(it != areas_data_.end())
    {
        return it->second.area_name_;
    }
    return NO_NAME;
}

std::vector<Coord> Datastructures::get_area_coords(AreaID id)
{

    auto it = areas_data_.find(id);
    if(it != areas_data_.end())
    {
        return it->second.area_cordinates_;
    }
    return {NO_COORD};
}

void Datastructures::creation_finished()
{
    // Replace this comment with your implementation
    // NOTE!! It's quite ok to leave this empty, if you don't need operations
    // that are performed after all additions have been done.

}


std::vector<PlaceID> Datastructures::places_alphabetically()
{

    std::vector<PlaceID> places_sorted;


    if(sorted_by_name_.empty())
        return {};

    for(const auto & i : sorted_by_name_)
    {
        places_sorted.push_back(i.second);
    }

    return places_sorted;
}

std::vector<PlaceID> Datastructures::places_coord_order()
{

    std::vector<PlaceID> places_sorted;
    if(sorted_by_coord_.empty())
        return {};
    for(std::map<Coord, PlaceID>::iterator it = sorted_by_coord_.begin(); it != sorted_by_coord_.end(); ++it)
    {
        places_sorted.push_back(it->second);
    }
    return places_sorted;



}

std::vector<PlaceID> Datastructures::find_places_name(Name const& name)
{

    std::vector<PlaceID> places_with_name;
    for(std::unordered_map<long long int, place_info>::iterator it = places_data_.begin(); it != places_data_.end(); ++it)
    {
        if(it->second.place_name_ == name)
        {
            places_with_name.push_back(it->first);

        }
    }

    return places_with_name;
}

std::vector<PlaceID> Datastructures::find_places_type(PlaceType type)
{

    std::vector<PlaceID> places_with_type;

    for(std::unordered_map<long long int, place_info>::iterator it = places_data_.begin(); it != places_data_.end(); ++it)
    {
        if(it->second.place_type_ == type)
        {
            places_with_type.push_back(it->first);

        }
    }
    return places_with_type;
}

bool Datastructures::change_place_name(PlaceID id, const Name& newname)
{



    if(places_data_.find(id)!= places_data_.end() )
    {
        Name old_name = places_data_[id].place_name_;

        const auto& its = sorted_by_name_.equal_range(old_name);
        for(auto it = its.first; it != its.second; ++it)
        {
            if(it->second==id)
            {
                places_data_[id].place_name_ = newname;
                sorted_by_name_.erase(it);
                sorted_by_name_.insert({newname,id});

            }
        }
        return true;
    }
    return false;
}

bool Datastructures::change_place_coord(PlaceID id, Coord newcoord)
{


    if(places_data_.find(id)!= places_data_.end())
    {
        Coord old_coord = places_data_[id].cordinates_;
        const auto& its = sorted_by_coord_.equal_range(old_coord);
        for(auto it = its.first; it != its.second; ++it)
        {
            if(it->second==id)
            {
                places_data_[id].cordinates_ = newcoord;
                sorted_by_coord_.erase(it);
                sorted_by_coord_.insert({newcoord,id});

            }


        }
        return true;
    }
    return false;

}

std::vector<AreaID> Datastructures::all_areas()
{

    std::vector<AreaID> areas;
    for(std::unordered_map<long int, area_info>::iterator it = areas_data_.begin(); it != areas_data_.end(); ++it)
    {
        areas.push_back(it->first);
    }
    return areas;
}

bool Datastructures::add_subarea_to_area(AreaID id, AreaID parentid)
{

    auto it = areas_data_.find(id);
    auto iter = areas_data_.find(parentid);
    if(it != areas_data_.end() && iter != areas_data_.end() && it->second.parent_ == -1)
    {

        it->second.parent_ = parentid;
        return true;
    }

    return false;
}

std::vector<AreaID> Datastructures::subarea_in_areas(AreaID id)
{



    if(areas_data_.find(id) == areas_data_.end())
    {
        return {NO_AREA};
    }
    if(loop_counter_== 0)
    {
        subareas_.clear();
    }
    if (areas_data_[id].parent_ != -1)
    {

        AreaID area = areas_data_[id].parent_;
        subareas_.push_back(area);
        ++loop_counter_;
        subarea_in_areas(area);

    }
    loop_counter_ = 0;
    return subareas_;
}

std::vector<PlaceID> Datastructures::places_closest_to(Coord xy, PlaceType type)
{

    std::vector<PlaceID> places_close;
    std::multimap<float, PlaceID> sorted_distances;

        for(auto iter = places_data_.begin(); iter != places_data_.end(); ++ iter)
        {
            if(type != PlaceType{7})
            {
                if(iter->second.place_type_ == type)
                {
                    float distance = sqrt(pow(iter->second.cordinates_.x-xy.x,2.0)+pow(iter->second.cordinates_.y-xy.y,2.0));
                    sorted_distances.insert(std::pair<float,PlaceID>(distance, iter->first));
                }

            }
            if(type == PlaceType{7})
            {
            float distance = sqrt(pow(iter->second.cordinates_.x-xy.x,2.0)+pow(iter->second.cordinates_.y-xy.y,2.0));
            sorted_distances.insert(std::pair<float,PlaceID>(distance, iter->first));
            }

        }
        for(auto it = sorted_distances.begin(); it != sorted_distances.end(); ++it)
        {
            places_close.push_back(it->second);
        }
        if(places_close.size() > 3)
        {
            places_close.resize(3);

        }
        return places_close;






    return {};
}

bool Datastructures::remove_place(PlaceID id)
{

    auto it = places_data_.find(id);
    if(it == places_data_.end())
    {
        return false;
    }
    const auto& iter = sorted_by_name_.equal_range(it->second.place_name_);
    auto name_iter = iter.first;
    while(name_iter != iter.second)
    {
        if(name_iter->second == id)
        {
            sorted_by_name_.erase(name_iter);
            break;
        }
        ++name_iter;
    }
    sorted_by_coord_.erase(places_data_[id].cordinates_);

    places_data_.erase(id);
    return true;



}

std::vector<AreaID> Datastructures::all_subareas_in_area(AreaID id)
{

    auto it = areas_data_.find(id);
    if(it == areas_data_.end())
    {
        return {NO_AREA};
    }
    if(another_counter_ == 0)
    {
        areas_subs_.clear();
    }
    for(auto iter= areas_data_.begin(); iter != areas_data_.end(); ++iter)
    {
        if(it->first == iter->second.parent_)
        {
            areas_subs_.push_back(iter->first);
            ++another_counter_;

            all_subareas_in_area(iter->first);
        }
    }
    another_counter_ = 0;
    return areas_subs_;
}

AreaID Datastructures::common_area_of_subareas(AreaID id1, AreaID id2)
{


    if(areas_data_.find(id1) != areas_data_.end() ||areas_data_.find(id2) != areas_data_.end())
    {
        std::vector<AreaID> first_parent_areas = subarea_in_areas(id1);
        std::vector<AreaID> second_parent_areas = subarea_in_areas(id2);;
        std::unordered_set<AreaID> ref;
        for(auto& i : first_parent_areas)
        {
            ref.insert(i);
        }
        for (auto& reg : second_parent_areas)
        {
            if(ref.find(reg) != ref.end())
            {
                AreaID parent_id = reg;
                return parent_id;
            }
        }



    }
    return NO_AREA;
}



