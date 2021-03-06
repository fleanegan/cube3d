#include "test_utils.h"

TEST(test_init, player_pos_set_to_middle_of_tile)
{
	t_map *map = parse_map("test/assets/dummy_map_minimal_north");

	t_player result = init_player(map);
	expect_point_eq(&result.pos, TILE_SIZE * 1.5, TILE_SIZE * 1.5, TILE_SIZE * 0.5);
	free_map(&map);
}

TEST(test_init, player_orientation_to_north)
{
	t_map *map = parse_map("test/assets/dummy_map_minimal_north");

	t_player result = init_player(map);
	expect_matrix_eq(result.orientation, euler2rot(0., 0., -90.));
	free_map(&map);
}

TEST(test_init, player_orientation_to_south)
{
	t_map *map = parse_map("test/assets/dummy_map_minimal_south");

	t_player result = init_player(map);
	expect_matrix_eq(result.orientation, euler2rot(0., 0., 90.));
	free_map(&map);
}