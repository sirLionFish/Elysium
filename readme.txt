🕹️ Project Name: Helix Tactics (Working Title)
📖 Overview
Warfare Tactics is a tactical turn-based strategy game inspired by titles like Conquest of Elysium and Total War: Warhammer. The game features a grid-based battlefield where players command units with unique roles, stats, and abilities. A high-level Director AI and individual Unit AIs determine each faction’s behavior. The system supports layered AI personalities (aggressive, supportive, defensive, etc.) and is designed to be eventually exposed via a web API or integrated into a game engine.

🚀 How to Start the Game (CLI-based)
Clone the repo:


bash:

Make

./start


🧩 Project Structure

.
├── main.c              # Game loop and user interaction
├── map.c / .h          # Grid generation and tile state
├── unit.c / .h         # Unit definitions, stats, and actions
├── action.c / .h       # Movement and combat resolution
├── ai.c / .h           # Behavior Trees and Unit AI
├── director.c / .h     # Director AI controlling overall strategy
├── utils.c / .h        # Helpers for printing, math, etc.
└── README.md           # You're here!


✅ Features (Implemented)
Grid-based battlefield

Units with different roles (e.g., Warrior, Healer, Archer)

Turn-based movement + basic attack system

AI personalities: aggressive, defensive, supportive, fearful, passive

Director AI that delegates tasks to unit AI

📋 TODO
 Add fog of war / vision range system

 Expand AI personalities with memory/state

 Introduce terrain effects and modifiers

 Allow multi-army factions with separate personalities

 Add healing, buffing, and status effects

 Implement UI layer or API for external control (e.g., browser or game engine)

 Unit animations and visual feedback (optional for non-CLI)

 Save/load game state

 Multiplayer support (turn-based hotseat or networked)

🔧 Function Responsibilities (Sample)
create_map(int width, int height)
Creates a 2D grid of tiles for the battlefield. Initializes terrain and tile states.

spawn_unit(UnitType type, int x, int y, Faction *faction)
Places a unit of a given type on the map with default stats and abilities.

perform_action(Unit *unit, Tile *target)
Interprets whether to move or attack based on the target tile. Delegates to move_unit or attack_unit.

run_director_ai(Faction *faction)
Evaluates the global game state and assigns goals to each unit based on personality and available data.

run_unit_ai(Unit *unit)
Executes decisions made by the Director AI: pathfinding, targeting, etc.

🧠 Context + Architecture
Functional Core + AI Shell: Game state is handled in a pure-functional manner wherever possible, while the AI system works as an outer shell that manipulates units.

AI Layers: The Director AI (macro) delegates to Unit AI (micro). Behavior Trees and personality contexts shape decisions.

Input Handling: The game uses automatic action selection based on the type of target clicked/touched. No manual "choose attack/move" menu.

⚠️ Known Pitfalls + Technical Debt
🌀 AI Evaluation Loop: Currently synchronous and not optimized — slows down with too many units.

🔂 Director-Unit Sync: Rare cases of desync between Director intent and unit ability due to state race.

🧠 Lack of Memory in AI: Units and factions do not currently track prior states, reducing depth.

🧱 Tile System: Terrain is hardcoded; no modular plugin support for new types yet.

🛠️ No Undo: Moves and actions cannot be reversed once executed — testing is risky.

🕳️ Error Handling: Minimal guard clauses — avoid out-of-bounds and null dereferences.

📚 How to Use (Development Workflow)
Start from main.c to understand the game loop.

Implement new unit types or abilities in unit.c.

Add actions or logic in action.c.

Expand AI in ai.c (for unit-level) or director.c (for faction-level).

Test new logic in isolation before integrating into the game loop.

🧪 Testing Tips
Use printf tracing to debug AI decisions and game state transitions.

Add unit test blocks in main.c using conditional flags.

Visualize map state frequently to detect unit positioning issues.
