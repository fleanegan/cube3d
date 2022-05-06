#include "test_utils.h"

/*
TEST(test_projection, looking_straight_on_wall_how_long_is_the_line)
{
	t_data		data;
	t_matrix	dir;
	t_point		p0;
	t_point		p1;
	data.map = parse_map("test/assets/wall_far_away");
	data.player = init_player(data.map);
	data.camera = init_camera();
	generate_direction_vector(&data.player.orientation, &dir);
	float distance_to_wall = calc_distance_to_obstacle(&data, &dir);

	//fixme
	raycast_one_slice(&data, 0., &p0, &p1);

	EXPECT_FLOAT_EQ(p0.y, data.player.pos.mat[2][0] + data.map->wall_height / 2. *  data.camera.distance_screen / distance_to_wall);
	EXPECT_FLOAT_EQ(p1.y, data.player.pos.mat[2][0] - data.map->wall_height / 2. *  data.camera.distance_screen / distance_to_wall);
}
*/

/*
	printf("yplayer: %f, h0 / 2: %f, hc: %f, dc: %f, do: %f\n",
		   data.player.pos.mat[2][0],
		   data.map->wall_height / 2. ,
		   data.camera.win_size.y_max / 2.f,
		   data.camera.distance_screen,
		   distance_to_wall);
 */