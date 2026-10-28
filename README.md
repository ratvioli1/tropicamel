# Tropicamel

A living board game. This README is also a living document if that's interesting to you. Expect this file to change a lot per-submission, I'm even about to continue working on it after submitting right now.

## Game Loop

Players go around the board buying and selling items.

The board has a home, mall, ship, and city, and factory section. Buy items, sell them across seas, and produce your own to sell more. Certain board spaces are designated sale/auction spaces, and interactive board spaces update your balance.

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

## Physical design and parts

The Oz64 is already running Linux on the main core and Arduino sketches on the small core. I have I2C OLEDs working if I want to incorporate those.

I have ordered parts for everything below, and they'll all be here by November 2nd:

- **Display:** A [7-inch Elecrow CrowPanel ESP32 display](https://www.amazon.com/dp/B0F8NFFH29): the center display, it has an 800×480 capacitive touchscreen, a built-in ESP32-S3, USB-C serial, a USB cable and acrylic case. The display ESP32 needs its own interface firmware and serial protocol and the Oz64 USB serial connection will need to be power needs to be tested.

- **Ship:** I'm getting a 5 V geared stepper to drive a string loop under the board, with a guided carriage piece and magnets coupling it to the ship above a thin surface. That avoids an exposed slot/rail, but the magnet's strength and fraction will need to be tested. I can do a slotted carriage though if that doesn't work out. I'll be using a home switch to find an endpoint and move to the midpoint and opposite endpoint for the two-turn crossing.

- **Day/night lighting:** I bought individually addressable RGB pixels and I'm going to put them under translucent 3D-printed diffusers in each section. Since they're RGB, the day can be warm and bright, sunset dusk orange, and night can be a dim blue. They come on a strip and are prewired to avoid soldering. I might need to use a 3.3 V-to-5 V data buffer for them, IDK yet.

- **Player detection:** Magnets in printed player bases and Hall sensor modules beneath special spaces.

- **Control and power:** The Arduino side can drive the motor driver inputs and read switches while the Linux side can manage game state and send commands between cores using the existing working setup. Motors and display will use a separate 5 V supply.

- **Turn button:** Pass a big red momentary button around the table. I'm buying a battery-powered ESP32-C3 to read the switch and sends a packet to the Oz64 via BLE if I can get that working, otherwise WiFi.

Parts are being shipped. My total was $236.48 so this all better be worth it.

- 1 × [Elecrow CrowPanel 7-inch ESP32 touch display](https://www.amazon.com/dp/B0F8NFFH29), $54.99, including a USB cable and acrylic case.
- 1 × [five 5 V 28BYJ-48 steppers and ULN2003 drivers](https://www.amazon.com/dp/B01CP18J4A), $14.99, for motion prototypes.
- 1 × [ten Hall sensor modules](https://www.amazon.com/dp/B0CFLNZK9M), $8.59, and [50 6 × 3 mm magnets](https://www.amazon.com/dp/B08TQMV921), $6.98, for reactive spaces and player pieces.
- 1 × [50 prewired 5 V WS2811 pixels](https://www.amazon.com/dp/B01AG923GI), $17.99, with 10 cm between lights.
- 1 × [5 V 10 A power adapter](https://www.amazon.com/dp/B0G4KXT4BL), $27.99, with screw-terminal adapter.
- 1 × [breadboard-compatible 74AHCT125 buffers](https://www.amazon.com/dp/B0GHN5GY56), $7.59, to shift the LED data signal from 3.3 V to 5 V.
- 1 × [six prewired endstops](https://www.amazon.com/dp/B08CDF3Q6T), $9.99, for motor motion homing.
- 1 × [lever connector assortment](https://www.amazon.com/dp/B0CJ5QF4Z2), $12.45, for solderless connections.
- 1 × [Mayouko foam-lined carrying case](https://www.amazon.com/dp/B091BXDX7G), $26.97, approximately 11.6 x 8.3 x 3.9 inches outside and 10.6 x 6.2 x 2.4 inches inside for my loose components.
- 1 × [100 mm red arcade button](https://www.amazon.com/dp/B01LZMANZ7), $12.99, [pre-soldered Seeed XIAO ESP32-C3](https://www.amazon.com/dp/B0DRNSV5CS), $10.99, and a 4.8 mm arcade switch wire harness, $9.99, for the wireless turn button.
- 1 × pack of 24 multicolored board-game pawns, $4.99.
- 1 × [three full-size 830-point solderless breadboards](https://www.amazon.com/dp/B01EV6LJ7G), $8.99, for assembling several prototypes at once.
- Existing breadboard, jumper wires, resistors and Makerspace 3D printer

## Timeline

- [ ] **Oct 30:** Order prototype parts; make a paper board playable with basic rules; get a turn button and a simple lighting effect working if there's still time.
- [ ] **Nov 6:** During exam prep, test a sensor and document the display UART and motor power plan; do a small motor/guide experiment if parts arrive.
- [ ] **Nov 13:** Demonstrate one reactive space and both existing OLEDs. Test the 7-inch display if available and prototype a moving mechanism.
- [ ] **Nov 22:** Integrate a playable physical board with 2–4 reactive spaces and prototype the ship and one city lift.
- [ ] **Dec 6:** Integrate remaining motion if prototypes work. Make startup, homing, reset and shutdown reliable and secure wiring.
- [ ] **Dec 13:** Playtest, fix the most disruptive problems, and prepare my presentation.
