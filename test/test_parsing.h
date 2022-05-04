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


TEST(testParsing, parse_basic_textures)
{
	t_map *map1 = parse("test/assets/basic_file.cub");

	EXPECT_FALSE(strcmp(map1->texture[TEXTURE_SO], "./path_to_the_south_texture"));
	EXPECT_FALSE(strcmp(map1->texture[TEXTURE_NO], "./path_to_the_north_texture"));
	EXPECT_FALSE(strcmp(map1->texture[TEXTURE_WE], "./path_to_the_west_texture"));
	EXPECT_FALSE(strcmp(map1->texture[TEXTURE_EA], "./path_to_the_east_texture"));
	EXPECT_EQ(map1->floor_color, 0xFF8000);
	EXPECT_EQ(map1->ceilling_color, 0x000040);
	free_map(&map1);
}

TEST(testParsing, duplicates_textures_error)
{
	t_map *map1 = parse("test/assets/duplicate_textures.cub");

	EXPECT_EQ(map1, nullptr);
}

TEST(testParsing, duplicates_colors_error)
{
	t_map *map1 = parse("test/assets/duplicate_colors.cub");

	EXPECT_EQ(map1, nullptr);
}

TEST(testParsing, texture_with_too_many_word)
{
	t_map *map1 = parse("test/assets/texture_with_too_many_word.cub");

	EXPECT_EQ(map1, nullptr);
}

TEST(testParsing, color_with_too_many_fields)
{
	t_map *map1 = parse("test/assets/color_with_too_many_fields.cub");

	EXPECT_EQ(map1, nullptr);
}

TEST(testParsing, line_with_bad_infos)
{
	t_map *map1 = parse("test/assets/bad_info_line.cub");

	EXPECT_EQ(map1, nullptr);
}

TEST(testParsing, crash_test)
{
	t_map *map1 = parse("test/assets/crash.cub");

	print_map_infos(map1);
	free_map(&map1);
}
