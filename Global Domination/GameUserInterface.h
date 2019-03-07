#pragma once
#include "Action.h"

#include "SDL.h"

#include "MainToolbarView.h"
#include "SDLCompositePane.h"

namespace global_domination {

	class GameModel;

	class GameUserInterface
	{
	public:
		GameUserInterface(GameModel& game_model);
		SDL_Rect getClientArea() const;
		void initialize(GameModel& game_model);
		bool isQuiting();
		void render();
		void respondToAction(Sint32 action);
		void respondToMouseClick(TYPES::ACTION_LIST action, int x, int y);
		void switchActiveControl(std::shared_ptr<SDLCompositePane> top_control);
		template <class T> void switchView();
		void update();
	private:
		std::shared_ptr<SDLCompositePane> active_control_;
		GameModel& game_model_;
		bool is_quiting_;
		SDL_Renderer *renderer_;
		std::unique_ptr<MainToolbarView> toolbar_;
		SDL_Window* window_;
	};

	
	template<class T>
	inline void GameUserInterface::switchView()
	{
		switchActiveControl(std::make_unique<T>(game_model_, window_, getClientArea()));
	}

}