#include <stdio.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    if (input == NULL || output == NULL) {
        return 1;
    }
    
    int target_apartment;          // 100 - искомая квартира
    int known_apartment, known_entrance, known_floor, floors_in_building;
    // known_apartment = 50, known_entrance = 2, known_floor = 4, floors_in_building = 9
    
    fscanf(input, "%d", &target_apartment);
    fscanf(input, "%d %d %d %d", &known_apartment, &known_entrance, &known_floor, &floors_in_building);

    // Вычисляем абсолютный номер этажа от начала дома (считая с 1)
    // (2-1)*9 + 4 = 1*9 + 4 = 13 - известная квартира на 13-м этаже от начала
    int absolute_floor_number = (known_entrance - 1) * floors_in_building + known_floor;
    
    int apartments_per_floor;
    
    // Ищем количество квартир на этаже
    for (apartments_per_floor = 1; apartments_per_floor <= known_apartment; apartments_per_floor++) {
        // Вычисляем этаж для известной квартиры при текущем apartments_per_floor
        // (50-1)/apartments_per_floor + 1 = 49/apartments_per_floor + 1
        int calculated_absolute_floor = (known_apartment - 1) / apartments_per_floor + 1;
        
        // Проверяем только совпадение этажа
        // При apartments_per_floor = 4: 49/4+1=12+1=13 ✓
        if (calculated_absolute_floor == absolute_floor_number) {
            break;  // Нашли: 4 квартиры на этаже
        }
    }

    // Квартир в подъезде: 4 * 9 = 36
    int apartments_per_entrance = apartments_per_floor * floors_in_building;
    
    // Вычисляем подъезд для целевой квартиры (100)
    // (100-1)/36 + 1 = 99/36 + 1 = 2 + 1 = 3 ✓
    int target_entrance = (target_apartment - 1) / apartments_per_entrance + 1;
    
    // Квартир после предыдущих подъездов: 100 - (3-1)*36 = 100 - 72 = 28
    int remaining_apartments = target_apartment - (target_entrance - 1) * apartments_per_entrance;
    
    // Вычисляем этаж для оставшихся квартир (28)
    // (28-1)/4 + 1 = 27/4 + 1 = 6 + 1 = 7 ✓
    int target_floor = (remaining_apartments - 1) / apartments_per_floor + 1;
    
    fprintf(output, "%d %d", target_entrance, target_floor);  // 3 7
    
    fclose(input);
    fclose(output);
    
    return 0;
}