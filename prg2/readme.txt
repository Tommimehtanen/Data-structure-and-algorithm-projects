struct way_info{
    way_info(WayID id, std::vector<Coord> way_coords,Coord first_cordinate, Coord last_cordinate, Distance distance):
        id(id),
        way_cordinates_(way_coords),
        first_cordinate_(first_cordinate),
        last_cordinate_(last_cordinate),
        distance(distance)
    {}
    WayID id;
    std::vector<Coord> way_cordinates_;
    Coord first_cordinate_;
    Coord last_cordinate_;
    Distance distance;

};
yllä olevaa struktia käytettiin siksi koska siihen oli kätevä tallentaa useita eri tietoja reittiin liittyen



std::unordered_map<WayID, std::shared_ptr<way_info>> ways_data_;


ylläolevaa unordered mappia käytettiin siksi, koskapiti löytää avaimen avulla reittejä ja niiden ei tarvinut olla järjestyksessä.
Tällöin unordered map on parempi kuin map.







std::map<Coord,std::vector<std::pair<WayID,Coord>>> crossroads_;


yllä oleva tietorakenne olivat lähinnä apuna route_any funktion toteutuksessa.





struct crossroad{
    Coord cordinates;
    Distance distance = 0;
    bool visited = false;
    std::vector<std::shared_ptr<way_info>> ways_from_crosroads;
    std::shared_ptr<way_info> last_way;
};

Yllä olevan struktin tarkoituksena oli kuvata yhtä risteystä.
Tiedot ovat struktissa koska tietoja tarvittiin suhteellisen paljon ja ne oli kätevä tallentaa struktiin.


std::unordered_map<Coord, std::shared_ptr<crossroad>, CoordHash> all_crossroads_;

Yllä olevaan tietorakenteeseen tallennettiin risteysten koordinaatteja vastaavia reittejä.
Tietorakenteeksi valittiin unorderedmap, koska sen ei tarvinut olla järjestyksessä ja sieltä piti löytää avaimilla tietoa.
