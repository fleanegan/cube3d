#include "test_utils.h"

TEST(testParsing, return_NULL_bad_file_name)
{
	t_map *map1 = parse("");
	t_map *map2 = parse("invalid_file_name");
	t_map *map3 = parse("map.cubbad");
	t_map *map4 = parse(".cub");
	t_map *map5 = parse("  .cub    ");

	EXPECT_EQ(map1, nullptr);
	EXPECT_EQ(map2, nullptr);
	EXPECT_EQ(map3, nullptr);
	EXPECT_EQ(map4, nullptr);
	EXPECT_EQ(map5, nullptr);
}


TEST(testParsing, return_NULL_error_opening_file)
{
	t_map *map1 = parse("test/assets/file_not_exist.cub");
	t_map *map2 = parse("test/assets/file_not_readable.cub");


	EXPECT_EQ(map1, nullptr);
	EXPECT_EQ(map2, nullptr);
}


TEST(testParsing, parse_textures)
{
	t_map *map1 = parse("test/assets/basic_file.cub");

	print_map_infos(map1);
	free_map(&map1);
}

//TEST(testParsing, return_NULL_if_no_valid_map_entered)
//{
//	t_map *map = parse_map("invalid_file_name");
//
//	EXPECT_EQ(map, nullptr);
//}
//
//TEST(test_parsing, get_map_dimensions_for_invalid_file_returns_1)
//{
//	int result = measure_map("invalid_file_name", NULL, NULL);
//
//	EXPECT_EQ(result, -1);
//}
//
//TEST(test_parsing, get_map_dimensions_for_file_with_one_entry)
//{
//	int	width;
//	int	height;
//
//	measure_map("test/assets/dummy_map_one_point", &width, &height);
//	
//	EXPECT_EQ(width, 1);
//	EXPECT_EQ(height, 1);
//}
//
//TEST(test_parsing, get_map_dimensions_for_file_with_one_row_and_two_columns)
//{
//	int	width;
//	int	height;
//
//	measure_map("test/assets/dummy_map_two_points", &width, &height);
//
//	EXPECT_EQ(width, 2);
//	EXPECT_EQ(height, 1);
//}
//
//TEST(test_parsing, create_empty_grid)
//{
//	t_map	*map = (t_map *) malloc(sizeof(t_map));
//	int		width = 2;
//	int		height = 2;
//	map->width = width;
//	map->height = height;
//
//	t_matrix	**res = new_grid(map);
//
//	EXPECT_NE(res, nullptr);
//	free_2d_array((void **) res);
//	free(map);
//}
//
//
//TEST(test_parsing, create_empty_map)
//{
//	int	width = 2;
//	int	height = 2;
//
//	t_map *res = new_map(width, height);
//
//	EXPECT_NE(res, nullptr);
//	free_map(&res);
//}
//
//
//TEST(test_parsing, creating_map_NULL_terminates_width)
//{
//	int	width = 2;
//	int	height = 2;
//
//	t_map *res = new_map(width, height);
//
//	EXPECT_NE(res, nullptr);
//	EXPECT_EQ(res->grid[width], nullptr);
//	free_map(&res);
//}
//
//TEST(test_parsing, return_minus_one_if_not_all_columns_equal_len)
//{
//	int	width;
//	int	height;
//
//	int 	result = measure_map("test/assets/dummy_map_malformed", &width, &height);
//
//	EXPECT_EQ(result, -1);
//}
//
//TEST(test_parsing, parse_map_with_one_point)
//{
//	t_map *map = parse_map("test/assets/dummy_map_one_point");
//	t_matrix *only_point = (*map->grid);
//
//	EXPECT_NE(map, nullptr);
//	EXPECT_NE(only_point, nullptr);
//	free_map(&map);
//}
//
//TEST(test_parsing, parse_one_line_with_one_column)
//{
//	char	*line = (char *) "1";
//	t_map	*map = new_map(1, 1);
//
//	parse_line(line, map, 0);
//
//	EXPECT_EQ(map->grid[0][0].mat[0][0], 0);
//	EXPECT_EQ(map->grid[0][0].mat[1][0], 0);
//	EXPECT_EQ(map->grid[0][0].mat[2][0], 1);
//	free_map(&map);
//}
//
//TEST(test_parsing, parse_one_line_with_two_columns)
//{
//	char	*line = (char *) "1 2";
//	t_map	*map = new_map(2, 1);
//
//	parse_line(line, map, 0);
//
//	EXPECT_EQ(map->grid[0][0].mat[0][0], 0);
//	EXPECT_EQ(map->grid[0][0].mat[1][0], 0);
//	EXPECT_EQ(map->grid[0][0].mat[2][0], 1);
//	EXPECT_EQ(map->grid[1][0].mat[0][0], 1);
//	EXPECT_EQ(map->grid[1][0].mat[1][0], 0);
//	EXPECT_EQ(map->grid[1][0].mat[2][0], 2);
//	free_map(&map);
//}
//
//TEST(test_parsing, parse_map_two_by_two)
//{
//	t_map *map = parse_map("test/assets/dummy_map_two_by_two");
//
//	EXPECT_NE(map, nullptr);
//	EXPECT_EQ(map->grid[0][0].mat[2][0], 0);
//	EXPECT_EQ(map->grid[1][0].mat[2][0], 1);
//	EXPECT_EQ(map->grid[0][1].mat[2][0], 2);
//	EXPECT_EQ(map->grid[1][1].mat[2][0], 3);
//	EXPECT_EQ(map->grid[0][0].mat[0][0], 0);
//	EXPECT_EQ(map->grid[1][0].mat[0][0], 1);
//	EXPECT_EQ(map->grid[0][1].mat[0][0], 0);
//	EXPECT_EQ(map->grid[1][1].mat[0][0], 1);
//	EXPECT_EQ(map->grid[0][0].mat[1][0], 0);
//	EXPECT_EQ(map->grid[1][0].mat[1][0], 0);
//	EXPECT_EQ(map->grid[0][1].mat[1][0], 1);
//	EXPECT_EQ(map->grid[1][1].mat[1][0], 1);
//
//	EXPECT_EQ(map->width, 2);
//	EXPECT_EQ(map->height, 2);
//	free_map(&map);
//}
//
//TEST(test_parsing, set_spawn_point)
//{
//	t_map *map = parse_map("test/assets/dummy_map_minimal_north");
//
//	EXPECT_EQ(map->spawn_point, &map->grid[1][1]);
//	free_map(&map);
//}
