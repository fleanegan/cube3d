#include "test_utils.h"

TEST(test_distance, player_facing_north_sees_a_wall_in_half_a_tile_distance)
{
	t_data	data;
	data.map = parse_map("test/assets/dummy_map_minimal_north");
	data.player = init_player(data.map);
	t_matrix	dir;
	generate_direction_vector(&data.player.orientation, &dir);

	float result = calc_distance_to_obstacle(&data, &dir);

	EXPECT_FLOAT_EQ(result, TILE_SIZE / 2.f);
	free_map(&data.map);
}

TEST(test_distance, player_facing_north_east_sees_a_wall_in_more_than_half_a_tile_distance)
{
	t_data	data;
	data.map = parse_map("test/assets/dummy_map_minimal_north");
	data.player = init_player(data.map);
	data.player.orientation = euler2rot(0., 0., -45.);
	t_matrix	dir;
	generate_direction_vector(&data.player.orientation, &dir);

	float result = calc_distance_to_obstacle(&data, &dir);

	EXPECT_FLOAT_EQ(result, TILE_SIZE * 0.5 / cos(45. * DEG2RAD));
	free_map(&data.map);
}

TEST(test_distance, player_two_fields_from_wall_facing_north)
{
	t_data	data;
	data.map = parse_map("test/assets/dummy_map_player_one_field_from_north");
	data.player = init_player(data.map);
	t_matrix	dir;
	generate_direction_vector(&data.player.orientation, &dir);

	float result = calc_distance_to_obstacle(&data, &dir);

	EXPECT_FLOAT_EQ(result, TILE_SIZE * 1.5f);
	free_map(&data.map);
}

TEST(test_distance, calculate_distance_to_closest_wall)
{
	t_data	data;
	data.map = parse_map("test/assets/dummy_map_player_one_field_from_north");
	data.player = init_player(data.map);
	data.player.orientation = euler2rot(0., 0., 135.);
	t_matrix	dir;
	generate_direction_vector(&data.player.orientation, &dir);

	float result = calc_distance_to_obstacle(&data, &dir);

	EXPECT_FLOAT_EQ(result, TILE_SIZE * 0.5 / cos(45. * DEG2RAD));
	free_map(&data.map);
}

TEST(test_distance, looking_up_will_find_ceiling)
{
	t_data	data;
	data.map = parse_map("test/assets/dummy_map_player_one_field_from_north");
	data.player = init_player(data.map);
	data.player.orientation = euler2rot(0., 90., 0.);
	t_matrix	dir;
	generate_direction_vector(&data.player.orientation, &dir);

	float result = calc_distance_to_obstacle(&data, &dir);

	EXPECT_FLOAT_EQ(result, TILE_SIZE * 0.5);
	free_map(&data.map);
}

TEST(test_distance, wall_in_east)
{
	t_data	data;
	data.map = parse_map("test/assets/debug_mirror_effect");
	data.player = init_player(data.map);
	t_matrix	dir;
	generate_direction_vector(&data.player.orientation, &dir);
	print_matrix(&dir);

	float result = calc_distance_to_obstacle(&data, &dir);

	EXPECT_FLOAT_EQ(result, TILE_SIZE * 1.5);
	free_map(&data.map);
}

TEST(test_distance, debug_mirror)
{
	t_data	data;
	data.map = parse_map("test/assets/debug_mirror_effect");
	data.player = init_player(data.map);
	data.player.orientation = euler2rot(0., 0., 180.);
	t_matrix	dir;
	generate_direction_vector(&data.player.orientation, &dir);
	print_matrix(&dir);

	float result = calc_distance_to_obstacle(&data, &dir);

	EXPECT_FLOAT_EQ(result, -1);
	free_map(&data.map);
}