#pragma once
class Features
{
public:
	static void Features::toggle_GodMod(bool toggle, Ped player);
	static void Features::toggle_Invisibility(bool toggle, Entity player);
	static void Features::toggle_super_jump(bool toggle, Player player);
	static void Features::never_wanted(bool toggle, Player player);
	static void Features::no_ragdoll(bool toggle, Player player, Ped player_ped);

	static void Features::set_player_rp(int amount);	
	static void Features::bypass_sell_timer();
	static void Features::unlock_purchases();
	static void Features::unlock_maxstats();
	static void Features::unlock_clothes();
	static void Features::unlock_LSC();
	static void Features::unlock_tattoos();
	static void Features::unlock_max_armor_snaks();
	static void Features::unlock_heist_vehicle();
	static void Features::unlock_wep_skin();
	static void Features::unlock_max_playtime();
	static void Features::unlock_chromerims();
	static void Features::unlock_explusive_shirts();
	static void Features::unlock_redidsign_character1();
	static void Features::unlock_skip_tuto();
	static void Features::unlock_trophies();
	static void Features::unlock_hairstyle();
	static void Features::unlock_purchases_wep();
	static void Features::unlock_clear_badsport();
	static void Features::unlock_roosvelt_listed();
	static void Features::unlock_clear_report();

	static void Features::fix_veh(Vehicle veh);
	static void Features::Max_veh(Vehicle veh);
	static void Features::set_plate(Vehicle veh);
	static void Features::color_loop(Vehicle veh, bool toggle);
	static void Features::veh_invisible(Vehicle veh, bool toggle);
	static void Features::flip_veh(Vehicle veh);
	static void Features::set_primary_color(Vehicle veh, int r, int g, int b);
	static void Features::set_secondary_color(Vehicle veh, int r, int g, int b);
	static void Features::set_neon_color(Vehicle veh, int r, int g, int b);
	static void Features::set_engine_rpm(Vehicle veh, float multiplier);
	static void Features::set_engine_torque(Vehicle veh, float multiplier);
	static void Features::set_light_multiplier(Vehicle veh, float multiplier);
	static void Features::set_plate_type(Vehicle veh, int index);

	static void Features::teleport_to_objective();
	static void Features::teleport_entity_to(Ped player, Ped playerTarget);
	static void Features::teleport_to_nearest_veh(Ped player);
	static void Features::teleport_to_waypoint(Ped player);

	static void Features::give_weap(Ped player);
	static void Features::explosive_ammo(Player player, bool toggle);
	static void Features::fire_ammo(Player player, bool toggle);
	static void Features::explode_player(Ped player);
	static void Features::Crash_player(Ped player);

	static void Features::fiveM_drop();
	static void Features::nineM_drop();

	static void Features::apply_vehicle_mod(Vehicle veh, int modtype, int modindex);
};
