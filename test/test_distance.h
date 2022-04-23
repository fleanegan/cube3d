#include "test_utils.h"

TEST(test_distance, player_facing_north_sees_a_wall_in_half_a_tile_distance)
{
	t_map *map = parse_map("test/assets/dummy_map_minimal_north");
	t_game_obj game_obj = init_game_obj(map);
	t_matrix dir;
	generate_direction_vector(&game_obj, &dir);

	float result = calc_distance_to_wall(&dir, &game_obj);

	EXPECT_FLOAT_EQ(result, TILE_SIZE / 2.f);
	free_map(&map);
}

TEST(test_distance, player_facing_north_east_sees_a_wall_in_more_than_half_a_tile_distance)
{
	t_matrix dir;
	t_map *map = parse_map("test/assets/dummy_map_minimal_north");
	t_game_obj game_obj = init_game_obj(map);
	game_obj.orientation = euler2rot(0., 0., 45.);
	generate_direction_vector(&game_obj, &dir);

	float result = calc_distance_to_wall(&dir, &game_obj);

	EXPECT_FLOAT_EQ(result, TILE_SIZE * 0.5 / cos(45. * DEG2RAD));
	free_map(&map);
}

TEST(test_distance, player_two_fields_from_wall_facing_north)
{
	t_map *map = parse_map("test/assets/dummy_map_player_one_field_from_north");
	t_game_obj game_obj = init_game_obj(map);
	t_matrix dir;
	generate_direction_vector(&game_obj, &dir);

	float result = calc_distance_to_wall(&dir, &game_obj);

	EXPECT_FLOAT_EQ(result, TILE_SIZE * 1.5f);
	free_map(&map);
}

// calculate_distance_to_closest_wall