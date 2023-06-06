import numpy as np

dist_matrix = [
    [0     , 0     , 0     , 0     , 0     , 194   , 0     , 427   , 0     , 0     , 304   , 0     , 727   , 956   , 560   ],
    [0     , 0     , 0     , 0     , 0     , 0     , 513   , 0     , 369   , 271   , 711   , 0     , 0     , 0     , 466   ],
    [0     , 0     , 0     , 210   , 0     , 0     , 0     , 128   , 0     , 0     , 0     , 135   , 500   , 0     , 0     ],
    [0     , 0     , 210   , 0     , 215   , 0     , 0     , 0     , 0     , 0     , 0     , 149   , 0     , 705   , 0     ],
    [0     , 0     , 0     , 215   , 0     , 0     , 0     , 0     , 0     , 0     , 0     , 0     , 1486  , 782   , 0     ],
    [194   , 0     , 0     , 0     , 0     , 0     , 0     , 0     , 0     , 0     , 480   , 0     , 640   , 957   , 162   ],
    [0     , 513   , 0     , 0     , 0     , 0     , 0     , 0     , 0     , 291   , 798   , 0     , 1205  , 0     , 239   ],
    [427   , 0     , 128   , 0     , 0     , 0     , 0     , 0     , 0     , 0     , 0     , 414   , 852   , 821   , 0     ],
    [0     , 369   , 0     , 0     , 0     , 0     , 0     , 0     , 0     , 470   , 934   , 0     , 0     , 0     , 1152  ],
    [0     , 271   , 0     , 0     , 0     , 0     , 291   , 0     , 470   , 0     , 0     , 0     , 0     , 0     , 0     ],
    [304   , 711   , 0     , 0     , 0     , 480   , 798   , 0     , 934   , 0     , 0     , 0     , 1032  , 0     , 407   ],
    [0     , 0     , 135   , 149   , 0     , 0     , 0     , 414   , 0     , 0     , 0     , 0     , 1066  , 727   , 0     ],
    [727   , 0     , 500   , 0     , 1486  , 640   , 1205  , 852   , 0     , 0     , 1032  , 1066  , 0     , 696   , 0     ],
    [956   , 0     , 0     , 705   , 782   , 957   , 0     , 821   , 0     , 0     , 0     , 727   , 696   , 0     , 0     ],
    [560   , 466   , 0     , 0     , 0     , 162   , 239   , 0     , 1152  , 0     , 407   , 0     , 0     , 0     , 0     ]
]
city_names = ['Lima', 'Arequipa', 'Trujillo', 'Chiclayo', 'Piura', 'Huancayo', 'Cusco', 'Chimbote', 'Tacna', 'Juliaca', 'Ica', 'Cajamarca', 'Pucallpa', 'Tarapoto', 'Ayacucho']

def nearest_neighbor(dist_matrix):
    num_cities = 15
    unvisited_cities = set(range(num_cities))
    current_city = np.random.choice(num_cities)
    print('Початкове місто:', city_names[current_city])
    tour = []
    total_distance = 0

    while unvisited_cities:
        tour.append(current_city)
        unvisited_cities.remove(current_city)
        nearest_distance = np.inf
        nearest_city = None

        for city in unvisited_cities:
            distance = dist_matrix[current_city][city]
            if distance > 0 and distance < nearest_distance:
                nearest_distance = distance
                nearest_city = city

        if nearest_city is None:
            break

        current_city = nearest_city
        total_distance += nearest_distance

    if len(tour) < num_cities:
        return None, None

    tour.append(tour[0])
    total_distance += dist_matrix[current_city][tour[0]]

    return tour, total_distance


tour,total_distance = nearest_neighbor(dist_matrix)

if tour is not None:
    city_tour = [city_names[i] for i in tour]
    city_tour = ' → '.join(city_tour)
    print("Маршрут:", city_tour)
    print("Довжина:", total_distance, "км")
else:
    print("Маршруту не знайдено.")

