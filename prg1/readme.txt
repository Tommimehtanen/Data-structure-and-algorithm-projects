Tässä toteutuksessa on käytetty useita eri tietorakenteita. Alla on tieorakenteet datastructures.hh tiedostosta ja niiden alla perusteltu tietorakenteiden valintoja.

struct place_info{
        Name place_name_;
        PlaceType place_type_;
        Coord cordinates_;
    };
    std::unordered_map<PlaceID,place_info> places_data_;


Yksittäiseen paikkaan liittyvät yllä olevat tiedot tuntui järkevimmältä toteuttaa structiin.
struktissa olevat paikan tiedot tallennettiin unordered_mapiin, PlaceID:n ollessa uniikki avain jokaiselle paikalle.
Tietorakenteeksi valittiin unordered_map, koska ei ole syytä pitää koko tietorakennetta kokoajan järjestyksessä avaimien mukaan.
Tämä tuntui siis tehokkaammalta kuin pelkkä map.







    std::multimap<Name, PlaceID> sorted_by_name_;
    std::map<Coord, PlaceID> sorted_by_coord_;

Yllä olevat tietorakenteet on olemassa siksi, koska ne parantivat huomattavasti useiden funktioiden tehokkuuksia.
Sorted_by_name_ multimap on järjestyksessä paikkojen nimien mukaan. Tietorakenteeksi valittiin multimap, koska paikkoja voi olla useita saman nimisiä.
Sorted_by_coord_ map sisältää paikkojen koordinaatit ja tunnuksen ja se on järjestetty koordinaattien mukaan.
Eri paikkoja ei voi olla täsmälleen samassa paikassa, joten tietorakenteeksi valittiin map multimapin sijaan, joka parantaa tehokkuutta.


    struct area_info{
        Name area_name_;
        std::vector<Coord> area_cordinates_;
        AreaID parent_;

    };
    std::unordered_map<AreaID,area_info> areas_data_;

Yksittäiseen alueen liittyvät tiedot kuten nimi, koordinaatit ja alue johon se kuuluu tuntui järkevältä toteuttaa struktina.
Struktin tiedot ja alueen tunnus tallennettiin unordered_mapiin, koska tarvetta pitää tietorakennetta kokoajan järjestyksessä ei ole.
Ratkaisu on tehokkaampi kuin järjestetty map.


    std::vector<AreaID> subareas_;
    std::vector<AreaID> areas_subs_;


Yllä olevat tietorakenteet on olemassa siksi, koska funktioista tuli paljon tehokkaampia tällä tavalla kuin, jos kaikki tieto alueista olisi aina kaivettava areas_data_ tietorakenteesta.
subareas_ vektori pitää sisällään tunnukset alueen alialueista. areas_subs_ taas pitää sisällään alueen isäntäalueet.

Päätietorakenteiden eli places_data_ ja areas_data_ lisäksi toteutetut tietorakenteet hieman hankaloittivat ohjelman toteuttamista,
mutta loppujen lopuksi ohjelmasta tuli paljon tehokkaampi näin toteutettuna kuin vain päätietorakenteita käyttäen.
