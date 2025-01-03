# Peace-Treaty-V1.2
Current status: In development (will not run)

Concept:
4x turn-based strategy game combining aspects of games like Civilizations, Hexonia, Polytopia, Lords Mobile, Rise of Kingdoms, and Infinity Kingdom with original ideas. Aim: A game with the semantics of a massively multiplayer strategy game like Lords Mobile but applied to the structure/procedures of a turn-based game like Civilizations.

Implementation:
- Design: The design is based on a coordinate-based system in which Provinces objects represent coordinates held in a double vector. Provinces are owned by a static Map object that creates and tracks the coordinate system. Provinces own Commanders objects that represent deployable units. Commanders own Troops objects that interact with other Troops in various ways, and these Troops have different tiers. Participants represent players (human and AI) that complete actions. Participants share ownership of Provinces with Map and share ownership of Commanders with Provinces-- Provinces and Commanders and are created on the stack and moved into vectors of the object that owns it.
- AI functionality (in design phase): This game is based on users choosing actions, and the AI functionality will work by randomly choosing actions. User actions as well as in-game events affect the probabilities of certain actions being chosen. For example, if a player attacks an AI, the AI is more likely to choose the Attack function, and within that, they are more likely to choose to attack their agressor rather than another Participant. Various actions add or subtract to this process of random access-- probabilities change dynamically to simulate responsiveness. The idea is to represent a neural network implementation.

Game experience:
- Users can choose from a variety of options such as building infrastructure, developing armies, training troops, and attacking others
- Users expand across the map and may attak or develop diplomatic relations with other users/bots
- Win conditions:
1) Defeat all other kingdoms (a kingdom dies when it has no provinces and no commanders)
2) Make peace with all other kingdoms (establish diplomatic superiority)
3) Defeat some kingdoms and make peace with all others (mixed approach)
- Attack functionaltiy: Train commanders (in charge of armies) and troops (basic army units) and use them to attack/defend provinces
- Diplomacy functionality: Defend other players' provinces with your troops, develop alliances, send resources, and send workers to help develop infrastruture in other kingdoms
1) The more involved with other kingdoms, the more diplomatic influence you have over them. If 50% + 1 of something came from you, you have diplomatic superiority over that kingdom
2) Example 1 - If a kingdom has 10 commanders and 1 or 5 were sent by you, you have diplomatic influence over them
3) Example 2 - If a kingdom has 10 commanders and 6 or more were sent by you, you have diplomatic influence
  
Graphics:
This is a console application and uses text for all game prompts and input.

Background/Skill Level:
My current C++ skill level is beginner. This project is based on a game I started my freshman year of high school in Computer Programming 1. I intend to continue working and developing the game as a life-long project to help me work on my skills. This game is not meant for release, but rather my own personal enjoyment. However, it is open source so others may use my work as a base for their own projects or to incorporate some of my ideas.
