void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();

	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	// int reset_month = 9, reset_day = 20;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

    if ( month < 12 )
    {
    	year = 2011;
        month = 12;
        day = 1;
		
		GetGame().GetWorld().SetDate( year, month, day, hour, minute );
	}

	// if ((month == reset_month) && (day < reset_day))
	// {
	// 	GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	// }
	// else
	// {
	// 	if ((month == reset_month + 1) && (day > reset_day))
	// 	{
	// 		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	// 	}
	// 	else
	// 	{
	// 		if ((month < reset_month) || (month > reset_month + 1))
	// 		{
	// 			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	// 		}
	// 	}
	// }
}

class CustomMission: MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		// this piece of code is recommended otherwise event system is switched on automatically and runs from default values
		// comment this whole block if NOT using Namalsk Survival
		// if ( m_EventManagerServer )
		// {
		// 	m_EventManagerServer.OnInitServer( true, 550, 1000, 2 );
		// 	// enable/disable event system, min time between events, max time between events, max number of events at the same time
		// 	// registering events and their probability
		// 	m_EventManagerServer.RegisterEvent( Aurora, 0.85 );
		// 	m_EventManagerServer.RegisterEvent( Blizzard, 0.4 );
		// 	m_EventManagerServer.RegisterEvent( ExtremeCold, 0.4 );
		// 	m_EventManagerServer.RegisterEvent( Snowfall, 0.6 );
		// 	m_EventManagerServer.RegisterEvent( EVRStorm, 0.35 );
		// 	m_EventManagerServer.RegisterEvent( HeavyFog, 0.3 );
		// }
	}
	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			float rndHlt = Math.RandomFloat( 0.45, 0.65 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}

	override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName)
	{
		Entity playerEnt;
		playerEnt = GetGame().CreatePlayer( identity, characterName, pos, 0, "NONE" );
		Class.CastTo( m_player, playerEnt );

		GetGame().SelectPlayer( identity, m_player );

		return m_player;
	}

	override void StartingEquipSetup(PlayerBase player, bool clothesChosen)
	{
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;

		itemClothing = player.FindAttachmentBySlotName( "Body" );
		if ( itemClothing )
		{
			SetRandomHealth( itemClothing );
			
			itemEnt = itemClothing.GetInventory().CreateInInventory( "BandageDressing" );
			if ( Class.CastTo( itemBs, itemEnt ) )
				itemBs.SetQuantity( 2 );

			string chemlightArray[] = { "Chemlight_White", "Chemlight_Yellow", "Chemlight_Green", "Chemlight_Red" };
			int rndIndex = Math.RandomInt( 0, 4 );
			itemEnt = itemClothing.GetInventory().CreateInInventory( chemlightArray[rndIndex] );
			SetRandomHealth( itemEnt );

			rand = Math.RandomFloatInclusive( 0.0, 1.0 );
			if ( rand < 0.35 )
				itemEnt = player.GetInventory().CreateInInventory( "Apple" );
			else if ( rand > 0.65 )
				itemEnt = player.GetInventory().CreateInInventory( "Pear" );
			else
				itemEnt = player.GetInventory().CreateInInventory( "Plum" );

			SetRandomHealth( itemEnt );
		}
		
		itemClothing = player.FindAttachmentBySlotName( "Legs" );
		if ( itemClothing )
			SetRandomHealth( itemClothing );
		
		itemClothing = player.FindAttachmentBySlotName( "Feet" );
	}
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}