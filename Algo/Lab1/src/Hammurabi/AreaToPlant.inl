#ifndef HAMMURABI_AREA_TO_PLANT_INL
#define HAMMURABI_AREA_TO_PLANT_INL

namespace hamurabi {

template<class T>
constexpr AreaToPlantResult AreaToPlant::New(const Acres area_to_plant, const Game<T> &game) noexcept {
    const auto area = game.Area();
    if (area_to_plant > area) {
        return NotEnoughArea{game};
    }
    const auto grain = game.Grain();
    if (area_to_plant > detail::AreaCanPlantWithGrain(grain)) {
        return NotEnoughGrain{game};
    }
    const auto population = game.Population();
    if (area_to_plant > detail::AreaCanPlantWithPopulation(population)) {
        return NotEnoughPeople{game};
    }
    return AreaToPlant{area_to_plant};
}

constexpr AreaToPlant::operator Acres() const noexcept {
    return area_to_plant_;
}

constexpr AreaToPlant::AreaToPlant(const Acres area_to_plant) noexcept
    : area_to_plant_{area_to_plant} {}

}

#endif //HAMMURABI_AREA_TO_PLANT_INL
