/* Copyright (C) 2016, Nikolai Wuttke. All rights reserved.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "base/warnings.hpp"
#include "engine/timing.hpp"
#include "loader/duke_script_loader.hpp"
#include "renderer/renderer.hpp"

RIGEL_DISABLE_WARNINGS
#include <SDL_events.h>
RIGEL_RESTORE_WARNINGS

#include <string>


namespace rigel {

struct IGameServiceProvider;
class UserProfile;

namespace engine {
  class TileRenderer;
}

namespace loader {
  class ResourceLoader;
}

namespace ui {
  class MenuElementRenderer;
  class DukeScriptRunner;
}


struct GameMode {
  /** Contains everything a mode needs */
  struct Context {
    const loader::ResourceLoader* mpResources;
    renderer::Renderer* mpRenderer;
    IGameServiceProvider* mpServiceProvider;
    ui::DukeScriptRunner* mpScriptRunner;
    loader::ScriptBundle* mpScripts;
    ui::MenuElementRenderer* mpUiRenderer;
    engine::TileRenderer* mpUiSpriteSheetRenderer;
    UserProfile* mpUserProfile;
  };

  virtual ~GameMode() = default;

  virtual void handleEvent(const SDL_Event& event) = 0;

  virtual void updateAndRender(engine::TimeDelta dt) = 0;
};


void runScript(GameMode::Context& context, const std::string& scriptName);

}
