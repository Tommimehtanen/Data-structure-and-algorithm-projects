// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <unordered_map>
#include <map>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <unordered_set>

// Types for IDs
using PlaceID = long long int;
using AreaID = long int;
using Name = std::string;
using WayID = std::string;

// Return values for cases where required thing was not found
PlaceID const NO_PLACE = -1;
AreaID const NO_AREA = -1;
WayID const NO_WAY = "!!No way!!";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Enumeration for different place types
// !!Note since this is a C++11 "scoped enumeration", you'll have to refer to
// individual values as PlaceType::SHELTER etc.
enum class PlaceType { OTHER=0, FIREPIT, SHELTER, PARKING, PEAK, BAY, AREA, NO_TYPE };

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;


};




// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary

struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
using Distance = int;

inline bool operator<(Coord c1, Coord c2)
{
    Distance distances =sqrt(pow(c1.x, 2.0)+ pow(c1.y, 2.0));
    Distance dist = sqrt(pow(c2.x,2.0)+pow(c2.y,2.0));
    if(distances == dist)
    {
        return c1.y < c2.y;
    }
    return distances < dist;

}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Type for a distance (in metres)


// Return value for cases where Duration is unknown
Distance const NO_DISTANCE = NO_VALUE;



// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: O(1)
    // Short rationale for estimate: Säiliön koon hakeminen on vakioaikaista
    int place_count();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Elementit tuhotaan yksitellen
    void clear_all();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Koko tietorakenne joudutaan käymään for-loopilla läpi
    std::vector<PlaceID> all_places();

    // Estimate of performance: O(n) theta(1)
    // Short rationale for estimate: Find komento on keskimäärin vakioaikainen ja unorderedmappiin lisääminen on vakioaikaista.
    bool add_place(PlaceID id, Name const& name, PlaceType type, Coord xy);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Huonoimmassa tapauksessa for-looppi käy koko tietorakenteen läpi.
    std::pair<Name, PlaceType> get_place_name_type(PlaceID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Huonoimmassa tapauksessa for-looppi käy koko tietorakenteen läpi.
    Coord get_place_coord(PlaceID id);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n)
    // Short rationale for estimate: Halutut arvot löytyvät sorted_by_name multimapista joten tiedot täytyy vain kopioida vektoriin.
    std::vector<PlaceID> places_alphabetically();

    // Estimate of performance: O(logn)
    // Short rationale for estimate: Halutut arvot löytyvät sorted_by_coord mapista joten arvot pitävät vain kopioida vektoriin.
    std::vector<PlaceID> places_coord_order();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Pahimmassa tapauksessa unorderedmapista etsittävä arvo on viimeisenä.
    std::vector<PlaceID> find_places_name(Name const& name);

    // Estimate of performance:O(n)
    // Short rationale for estimate: Pahimmassa tapauksessa unorderedmapista etsittävä arvo on viimeisenä.
    std::vector<PlaceID> find_places_type(PlaceType type);

    // Estimate of performance: O(k) theta (logn)
    // Short rationale for estimate: Ensin etsitään oikea nimi ja pahimmassa tapauksessa kaikki paikat on nimetty samalla nimellä.
    // tällöin funktion tehokkuus on lineaarinen koska joudutaan käymään kaikki alkiot läpi. Keskimäärin aikaa kuluu theta (logn).
    bool change_place_name(PlaceID id, Name const& newname);

    // Estimate of performance: O(k) theta (logn)
    // Short rationale for estimate: Ensin etsitään oikea nimi ja pahimmassa tapauksessa kaikki paikat on nimetty samalla nimellä.
    // tällöin funktion tehokkuus on lineaarinen koska joudutaan käymään kaikki alkiot läpi. Keskimäärin aikaa kuluu theta (logn).
    bool change_place_coord(PlaceID id, Coord newcoord);

    // We recommend you implement the operations below only after implementing the ones above

    // Estimate of performance: O(n), theta(1)
    // Short rationale for estimate: Unordered mappiin lisääminen on keskimääräisesti vakioaikaista. Phammillaan lineaarista.
    bool add_area(AreaID id, Name const& name, std::vector<Coord> coords);

    // Estimate of performance: O(n), theta(1)
    // Short rationale for estimate: Unordered mapista etsiminen on ylensä vakioaikaista mutta pahimmassa tapauksessa lineaarista.
    Name get_area_name(AreaID id);

    // Estimate of performance: O(n), theta(1)
    // Short rationale for estimate: Unordered mapista etsiminen on ylensä vakioaikaista mutta pahimmassa tapauksessa lineaarista.
    std::vector<Coord> get_area_coords(AreaID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Koko tietorakenne käydään läpi ja arvot kopioidaan vektoriin.
    std::vector<AreaID> all_areas();

    // Estimate of performance: O(1)
    // Short rationale for estimate: unorderedmapista tietyn etsintä on vakioaikaista ja tietorakenteen parent_ attribuutin muuttaminen on myös vakioaikaista.
    bool add_subarea_to_area(AreaID id, AreaID parentid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Alueen kaikki "ylemmät" alueet käydään läpi joten tehokkuus on lineaarista.
    std::vector<AreaID> subarea_in_areas(AreaID id);

    // Non-compulsory operations

    // Estimate of performance:
    // Short rationale for estimate:
    void creation_finished();

    // Estimate of performance: O(n)
    // Short rationale for estimate: Rekursiivinen funktio käy kaikki alueen subareat läpi kerran.
    std::vector<AreaID> all_subareas_in_area(AreaID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Kaikki paikat käydään läpi joten tehokkuus on lineaarista.
    std::vector<PlaceID> places_closest_to(Coord xy, PlaceType type);

    // Estimate of performance: O(n), theta(1)
    // Short rationale for estimate: Etsitään iteraattorin sijainti halutun id:n kohdalta ja poistetaan haluttu alkio tietorakenteista.
    bool remove_place(PlaceID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: Molemmille alueille kutsutaan subarea_in_areas joka on O(2n)
    // Toinen vektoreista muutetaan järjestämättömäksi setiksi ja toisen vektorin avulla etsitään yhteinen alue johon kuluu aikaa 2n.
    // Eli yhteensä aikaa kuluu O(4n) eli asymptoottinen tehokkuus on O(n).
    AreaID common_area_of_subareas(AreaID id1, AreaID id2);

private:
    // Add stuff needed for your class implementation here
    struct place_info{
        Name place_name_;
        PlaceType place_type_;
        Coord cordinates_;
    };
    std::unordered_map<PlaceID,place_info> places_data_;
    std::multimap<Name, PlaceID> sorted_by_name_;
    std::map<Coord, PlaceID> sorted_by_coord_;

    struct area_info{
        Name area_name_;
        std::vector<Coord> area_cordinates_;
        AreaID parent_;

    };
    std::unordered_map<AreaID,area_info> areas_data_;
    std::vector<AreaID> subareas_;
    int loop_counter_;
    std::vector<AreaID> areas_subs_;
    int another_counter_;



};

#endif // DATASTRUCTURES_HH
