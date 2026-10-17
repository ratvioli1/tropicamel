# Tropicamel

A living board game. This README is also a living document if that's interesting to you. Expect this file to change a lot per-submission, I'm even about to continue working on it after submitting right now.

## Game Loop

Players go around the board buying and selling items.

The baord has a home, mall, ship, and city, and factory section. Buy items, sell them across seas, and produce your own to sell more. Certain board spaces are designated sale/auction spaces, and interactive board spaces update your balance.

Like Monopoly, there's a Free Parking-esc space where you have the chance to snatch community funds. But in this game, community funds help build projects on the board, so taking them for yourself is a strategy.

### Home

Where all players start.

### Mall

A free market. Players sell items to other players here, and the game starts with several items already at the mall for sale. Companies on the screen can sell items too.

### Ship

Only one player can be on the ship at once. This creates an intentional bottleneck.

The ship takes two turns to cross.

While you're on the ship, you can sell items that are requested by companies, listed on the display.

### City

Changes throughout the game. At the start of the game, the city isn't very developed, but more buildings start to pop up. My idea for this are 4 city states, the first being no city and the last being a full city. Each state-delta is a different height so when resting, the top of the city is flat to the board. It'd be pretty small, and state deltas are culmulative. I have an idea on how to get this to work with a linear or rotational servo motor and I want to test it with a rotational one from D&M 401 first.

### Factory

Where you passively gain income. Some cards are factory cards, it means that they slowly increase your balance over time. You get to collect your factory money every time you pass the factory.

## Timeline

- [ ] **Oct 23:** One display and some lighting working at the same time and button advances game time (a turn). Potentially my second screen as well since I have two I2C displays working at the same time.
- [ ] **Oct 30:** Paper board game is playable and I complete the day/night cycle lighting/effects that I want
- [ ] **Nov 6:** Exam prep is more important, just look into implementing sensor spaces
- [ ] **Nov 13:** A working reactive space and both displays working.
- [ ] **Nov 22:** Integrated physical board with 2–4 reactive spaces; playable from start to finish
- [ ] **Dec 6:** Startup/reset/shutdown reliably works and the wiring is secured
- [ ] **Dec 13:** Playtest (ideally with other students) to have stuff to show off during my presentation
