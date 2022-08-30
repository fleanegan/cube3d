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


	EXPECT_EQ(map1, nullptr);
}


TEST(testParsing, parse_basic_textures)
{
	t_map *map1 = parse("test/assets/basic_file.cub");

	if (map1 != NULL)
	{
		EXPECT_FALSE(strcmp(map1->texture_name[TEXTURE_SO], "./path_to_the_south_texture"));
		EXPECT_FALSE(strcmp(map1->texture_name[TEXTURE_NO], "./path_to_the_north_texture"));
		EXPECT_FALSE(strcmp(map1->texture_name[TEXTURE_WE], "./path_to_the_west_texture"));
		EXPECT_FALSE(strcmp(map1->texture_name[TEXTURE_EA], "./path_to_the_east_texture"));
		print_map_infos(map1);
		free_map(&map1);
	}
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

TEST(testParsing, color_with_bad_format)
{
	t_map *map1 = parse("test/assets/color_with_bad_format.cub");

	EXPECT_EQ(map1, nullptr);
}

TEST(testParsing, invalid_value_in_map)
{
	t_map *map1 = parse("test/assets/invalid_value_in_map.cub");

	EXPECT_EQ(map1, nullptr);
}

TEST(testParsing, not_closed_with_wall)
{
	t_map *map1 = parse("test/assets/not_close_with_wall.cub");

	EXPECT_EQ(map1, nullptr);
}

TEST(testParsing, map_with_empty_line)
{
	t_map *map1 = parse("test/assets/map_with_empty_line.cub");

	EXPECT_EQ(map1, nullptr);
}

TEST(testParsing, multiple_spawnpoints_are_not_allowed)
{
	t_map *map1 = parse("test/assets/multiple_spawnpoints.cub");

	EXPECT_EQ(map1, nullptr);
}

TEST(testParsing, no_spawnpoint_is_not_allowed)
{
	t_map *map1 = parse("test/assets/no_spawnpoints.cub");

	EXPECT_EQ(map1, nullptr);
}

TEST(testParsing, only_spawn_point_is_not_allowed)
{
	t_map *map1 = parse("test/assets/only_spawn_point.cub");

	EXPECT_EQ(map1, nullptr);
}

TEST(testParsing, crash_test)
{
	t_map *map1 = parse("test/assets/crash.cub");

	print_map_infos(map1);
	free_map(&map1);
}
