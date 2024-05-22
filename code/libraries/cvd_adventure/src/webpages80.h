const char notes_txt80[] PROGMEM = R"rawliteral(
Test text file

Nothing here now

)rawliteral";

const char index_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Welcome to the 3000 Society Cowboys vs Dinosaurs Badge</h1>
<p>You have found the Cowboys vs Dinosaurs Badge Adventure Game<p/>
<p>This is a simple little choose your own adventure style game themed for the badge. We hope you enjoy it.</p>
<p>Start your journey below.</p>

<img alt="3000 Society Logo" width="400" height="224"
src='data:image/jpeg;base64,/9j/2wCEAAEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBAQEBA
QEBAQEBAQEBAQECAgICAgICAgICAgMDAwMDAwMDAwMBAQEBAQEBAgEBAgICAQICAwMDAwMDAwMDA
wMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDA//dAAQAGf/uAA5BZG9iZQBkw
AAAAAH/wAARCABwAMgDABEAAREBAhEB/8QAjwAAAgMBAAIDAQAAAAAAAAAACgsACAkHBAYBAwUCA
QEBAQAAAAAAAAAAAAAAAAAAAQIQAAAHAAIBAwQBAwIDBAsAAAECAwQFBgcICREAChITFBUhMRYXI
iNBGDJCGiRRYRklJzM2OVNxd7bwEQEAAQQBAwUBAQAAAAAAAAAAAREhMfBRQXGxYYGRocES4f/aA
AwDAAABEQIRAD8AP49BPQT0E9BPQT0E9BPQT0E9BPQT0E9BPQT0E9BPQT0E9APhxg9wNxy1/s75R
9ZGojFZ1fs83GcynjXoCC7tWn7VIVJiyiLfnU06WVdJVrU4y8x0snGiY6cbPNkyNkfoSJEUJDVOM
7u2tOBB/rKOdX/YMlyhl+S1LUc6zWO8AP39/u1apzLwbz8R+6sUnHIeDAUfH+X78elJGbOr97/T5
i6z1tdewXju8cx6ooO22c2Z9s7hJYoeTpAhjsXe1VTpj+jAQphKYPiPgQEPV/mVpK7vE3lXj/NfC
KdyUwKQsU3j+hOLKWjWSy1KfpDyzxtXs8xUXc+xrtqZRliawkhLQbgWajtq2UcNylVBMCHKIpiiT
FFjvUH/0DCOxLsa40dYvHqW5D8l7I8ZxAPAgKNRK0izktC1O5rNlnTSoUWEePo5u7fmbIHXcuXK7
ZgwbEMq5WTL8fkC6vmP7vfs73iyyqHGpagcM8yFZVKFh6hWK1qulLxphAShatG06uy8U5khEB8LQ
kDAgmQQL4OYBUMGfEL7i7upgZVpMNOfWounLNcq6baarOVWCKWMU4HFN3CzdAfxLxAwh4EiiJi/H
9eAD0BDvW57zK+NLVX827Ocxrk1SZJ02jVOSmGV97DWiplW8JBM6HkSTqRirhFkcqgo7cVo0U7Zs
0zfbxUiuJUzAcFrPN3izinE+T5vXvZKi34wsKFE6Ox1SJkE5yEtNbsaLQ9SCmhGiuvaJi5OZFs1i
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
Fprf6yEQzaoqCJ0xEQ0I9B//9k=
' />

<h2>Let the Adventure Begin!</h2>
<p>As you walk across a desolate landscape you see the table in the distance.  The challenge was made and accepted and now you walk to meet it.  As you get closer you can start to make out details about your competitors.  They are ugly and the sight of them causes bile to form in the back of your throat.  You can’t believe that your leader agreed to this card game to determine which group gets to stay in this land and which will be exiled.  Killing them all would make much more sense than leaving the fate of your group to the luck of a game. Maybe an opportunity will present itself that will allow you to sway luck in your favor during the game.</p>
<p>You must do whatever is necessary to ensure that the your group prevails.</p>
<p>This is about the very survival of the:</p>

<ul>
  <li><a href="c0.html">COWBOYS</a></li>
  <li><a href="d0.html">DINOSAURS</a></li>
</ul>
<p></p>
<br>

</body>
</html>
)rawliteral";

const char c0_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Cowboys</h1>
<p>You approach the table and take your seat directly across from one of those large beasts.  It looks at you with murder in its eyes.  A chill infects your spine as you fully realize the stakes of this game.</p>
<p>Before the game begins you decide to</p>
<ul>
  <li><a href="c11.html">taunt the dinosaur across the table from you.</a></li>
  <li><a href="c12.html">return the murderous stare but say nothing.</a></li>
  <li><a href="c13.html">laugh out loud as if this game is nothing but a fun time.</a></li>
</ul>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char c11_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Cowboys</h1>
<p>The dinosaur across from you stands and growls at you as its large jaw opens.  Before you can react, it lunges at you.  The last thing you see are rows of large teeth glistening with saliva before the dinosaur consumes your head in one bite.</p>
<h2>YOU ARE DEAD</h2>
<h2>GAME OVER</h2>
<p></p>
<br>
<p><a href="/">Try Again</a></p>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char c12_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Cowboys</h1>
<p>Tensions remain high as the game gets under way.  As the cards are being dealt one card is tossed between you and a dinosaur and you both reach for the card.  One of the dinosaur’s claws scratches your hand drawing blood.</p>
<p>You decide to</p>
<ul>
  <li><a href="c11.html">attack the dinosaur since it drew first blood!</a></li>
  <li><a href="c21.html">continue the game as if nothing happened.</a></li>
  <li><a href="c22.html">slowly remove your gun from its holster and level it at the dinosaur under the table while acting as if it’s nothing.</a></li>
</ul>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char c13_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Cowboys</h1>
<p>Tensions lower as the game gets under way.  Cards are dealt and hands are played.  The game seems evenly matched. This worries you since you thought your experience at cards would give you an advantage.</p>
<p>You decide to</p>
<ul>
  <li><a href="c21.html">continue the game and hope luck comes your way.</a></li>
  <li><a href="c22.html">slowly remove your gun from its holster and level it at the dinosaur under the table while acting normal.</a></li>
</ul>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char c21_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Cowboys</h1>
<p>You are dealt a low card straight, but four of the five cards are the same suit. You can keep these cards or discard the one odd suit to try to upgrade your straight to a flush or maybe even a straight-flush.</p>
<p>Are you feeling lucky or want to play it safe?</p>
<ul>
  <li><a href="c31.html">I’m feeling lucky, let’s do this!</a></li>
  <li><a href="c32.html">The bird in hand is looking good, let it play.</a></li>
</ul>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char c22_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Cowboys</h1>
<p>You see an opportunity to kill both dinosaurs before either can react.  If you do this, you will need to come up with a story about how they were cheating to get this to fly with leaders from both sides.</p>
<p>You decide to </p>
<ul>
  <li><a href="c33.html">Kill them and make your case to the leaders.</a></li>
  <li><a href="c32.html">It’s not worth the risk, just play your cards.</a></li>
</ul>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char c31_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Cowboys</h1>
<p>Luck is on your side! You draw a flush and win the hand putting your team on top.  Another big win like this will bring this game to a close.  The next deal leaves you with another big opportunity.  You have been dealt the Ten of hearts and diamonds as well as the Queen of hearts and diamonds with the Jack of hearts.  You can discard up to two cards.</p>
<p>You decide to </p>
<ul>
  <li><a href="c41.html">Discard the Ten and Queen of diamonds and try for a flush or a straight-flush.</a></li>
  <li><a href="c42.html">Discard the Jack and try for a full house.</a></li>
  <li><a href="c43.html">Discard nothing and try to bluff with two pair.</a></li>
</ul>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char c32_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Cowboys</h1>
<p>Playing it safe didn’t work out and you lost big. Another loss like this will bring this game to a close.  The next deal leaves you with another big opportunity.  You have been dealt the Ten of hearts and diamonds as well as the Queen of hearts and diamonds with the Jack of hearts.  You can discard up to two cards.</p>
<p>You decide to </p>
<ul>
  <li><a href="c44.html">Discard the Ten and Queen of diamonds and try for a flush or a straight-flush.</a></li>
  <li><a href="c45.html">Discard the Jack and try for a full house.</a></li>
  <li><a href="c46.html">Discard nothing and try to bluff with two pair.</a></li>
</ul>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char c33_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Cowboys</h1>
<p>You shoot the first dinosaur fatally but by the time you move your gun around for your second target it’s gone.  That dinosaur has jumped from the table and has started running back to its pack.  You have no hope of catching it and your gambit has FAILED!  This will be reported to the leaders and counted as a game forfeit.  Your group will be forced into exile leaving this land to be ruled by the dinosaurs.</p>
<h2>YOU HAVE FAILED</h2>
<h2>GAME OVER</h2>
<p></p>
<br>
<p><a href="/">Try Again</a></p>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char c41_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Cowboys</h1>
<p>Luck has failed you! You threw away two pair only to get beat by a lower two pair then what you were holding at the start. The dinosaurs have taken the lead. Another loss like this will bring this game to a close.  The next deal leaves you with A, A, K, Q, J.</p>
<p>You decide to </p>
<ul>
  <li><a href="c51.html">Hold onto the Ace pair and try for three of a kind.</a></li>
  <li><a href="c52.html">Discard an Ace and try for a straight.</a></li>
</ul>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char c42_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Cowboys</h1>
<p>Luck has failed you! You ended up with two pair which was beat by a full house. The dinosaurs have taken the lead. Another loss like this will bring this game to a close.  The next deal leaves you with A, A, K, Q, J.</p>
<p>You decide to </p>
<ul>
  <li><a href="c51.html">Hold onto the Ace pair and try for three of a kind.</a></li>
  <li><a href="c52.html">Discard an Ace and try for a straight.</a></li>
</ul>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char c43_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Cowboys</h1>
<p>The bluff worked! It looks like your skill at cards was enough to turn the tide.</p>
<p>You won the hand and the game!  The dinosaurs leave in defeat to be exiled from this land.</p>
<h2>COWBOYS ARE VICTORIOUS</h2>
<h2>YOU WIN!</h2>
<p></p>
<br>
<p><a href="/">Play Again</a></p>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char c44_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Cowboys</h1>
<p>Luck has failed you! You threw away two pair only to get beat by a lower two pair then what you were holding at the start. The dinosaurs have won the hand and the game! You will be forced into exile leaving this land to be ruled by the dinosaurs.</p>
<h2>YOU HAVE LOST</h2>
<h2>GAME OVER</h2>
<p></p>
<br>
<p><a href="/">Try Again</a></p>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char c45_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Cowboys</h1>
<p>Luck has failed you! You ended up with two pair which was beat by a full house. The dinosaurs have won the hand and the game! You will be forced into exile leaving this land to be ruled by the dinosaurs.</p>
<h2>YOU HAVE LOST</h2>
<h2>GAME OVER</h2>
<p></p>
<br>
<p><a href="/">Try Again</a></p>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char c46_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Cowboys</h1>
<p>The bluff worked!  You won the hand.  It’s a close game and the bets are high enough now that one hand can win or lose the whole thing.  The next deal leaves you with A, A, K, Q, J.</p>
<p>You decide to </p>
<ul>
  <li><a href="c51.html">Hold onto the Ace pair and try for three of a kind.</a></li>
  <li><a href="c52.html">Discard an Ace and try for a straight.</a></li>
</ul>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char c51_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Cowboys</h1>
<p>You got your third Ace, but a dinosaur beat you with a low card straight.  This was for all the marbles, and you came up short. The dinosaurs have won the hand and the game! You will be forced into exile leaving this land to be ruled by the dinosaurs.</p>
<h2>YOU HAVE LOST</h2>
<h2>GAME OVER</h2>
<p></p>
<br>
<p><a href="/">Try Again</a></p>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char c52_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Cowboys</h1>
<p>You got your Ten and made the high card straight! One of the dinosaurs had a low card straight that was not enough. You won the hand and the game!  The dinosaurs leave in defeat to be exiled from this land.</p>
<h2>COWBOYS ARE VICTORIOUS</h2>
<h2>YOU WIN!</h2>
<p></p>
<br>
<p><a href="/">Play Again</a></p>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char d0_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Dinosaurs</h1>
<p>You approach the table and take your seat directly across from one of those small smelly walking meals.  It looks at you with murder in its eyes.  Knowing what that gun on its hip has done to others in your pack you fully realize the stakes of this game.</p>
<p>Before the game begins you decide to</p>
<ul>
  <li><a href="d11.html">growl with exposed teeth at the cowboy across the table from you.</a></li>
  <li><a href="d12.html">return the murderous stare but do nothing.</a></li>
  <li><a href="d13.html">pick a bit of flesh from your teeth with indifference to the game as if it is nothing.</a></li>
</ul>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char d11_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Dinosaurs</h1>
<p>The cowboy across from you stands and draws his gun at a speed you didn’t think possible.  Before you can react, it aims at your head and pulls the trigger. The last thing you see is the muzzle flash as the bullet enters your skull. </p>
<h2>YOU ARE DEAD</h2>
<h2>GAME OVER</h2>
<p></p>
<br>
<p><a href="/">Try Again</a></p>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char d12_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Dinosaurs</h1>
<p>Tensions remain high as the game gets under way.  As the cards are being dealt one card is tossed between you and a cowboy and you both reach for the card.  One of the cowboy’s hands touches yours. This hot slimy filth is desecrating your skin.</p>
<p>You decide to</p>
<ul>
  <li><a href="d11.html">attack the cowboy for its insolence!</a></li>
  <li><a href="d21.html">continue the game as if nothing happened.</a></li>
  <li><a href="d22.html">use this opportunity to palm a card for use later.</a></li>
</ul>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char d13_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Dinosaurs</h1>
<p>Tensions lower as the game gets under way.  Cards are dealt and hands are played.  The game seems evenly matched. This worries you since you thought your experience at cards would give you an advantage.</p>
<p>You decide to</p>
<ul>
  <li><a href="d21.html">continue the game and hope luck comes your way.</a></li>
  <li><a href="d22.html">use this opportunity to palm a card for use later.</a></li>
</ul>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char d21_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Dinosaurs</h1>
<p>You are dealt a low card straight, but four of the five cards are the same suit. You can keep these cards or discard the one odd suit to try to upgrade your straight to a flush or maybe even a straight-flush.</p>
<p>Are you feeling lucky or want to play it safe?</p>
<ul>
  <li><a href="d31.html">I’m feeling lucky, let’s do this!</a></li>
  <li><a href="d32.html">The bird in hand is looking good, let it play.</a></li>
</ul>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char d22_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Dinosaurs</h1>
<p>You see an opportunity to use your palmed card to give you a winning hand. But the cowboys are eyeing you closely so it will be a risky move.  Can you pull off the card swap without them noticing?</p>
<p>You decide to </p>
<ul>
  <li><a href="d33.html">Attempt the card swap to give you the winning hand.</a></li>
  <li><a href="d32.html">It’s not worth the risk, just play your cards.</a></li>
</ul>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char d31_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Dinosaurs</h1>
<p>Luck is on your side! You draw a flush and win the hand putting your team on top.  Another big win like this will bring this game to a close.  The next deal leaves you with another big opportunity.  You have been dealt the Ten of clubs and spades as well as the Queen of clubs and spades with the Jack of clubs.  You can discard up to two cards.</p>
<p>You decide to </p>
<ul>
  <li><a href="d41.html">Discard the Ten and Queen of spades and try for a flush or a straight-flush.</a></li>
  <li><a href="d42.html">Discard the Jack and try for a full house.</a></li>
  <li><a href="d43.html">Discard nothing and try to bluff with two pair.</a></li>
</ul>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char d32_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Dinosaurs</h1>
<p>Playing it safe didn’t work out and you lost big. Another loss like this will bring this game to a close.  The next deal leaves you with another big opportunity.  You have been dealt the Ten of clubs and spades as well as the Queen of clubs and spades with the Jack of clubs.  You can discard up to two cards.</p>
<p>You decide to </p>
<ul>
  <li><a href="d44.html">Discard the Ten and Queen of spades and try for a flush or a straight-flush.</a></li>
  <li><a href="d45.html">Discard the Jack and try for a full house.</a></li>
  <li><a href="d46.html">Discard nothing and try to bluff with two pair.</a></li>
</ul>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char d33_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Dinosaurs</h1>
<p>You attempt to swap your palmed card and are caught by the cowboy closest to you who draws his gun on you. You have no hope of turning this around since you have been CAUGHT!  This will be reported to the leaders and counted as a game forfeit.  Your group will be forced into exile leaving this land to be ruled by the cowboys.</p>
<h2>YOU HAVE FAILED</h2>
<h2>GAME OVER</h2>
<p></p>
<br>
<p><a href="/">Try Again</a></p>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char d41_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Dinosaurs</h1>
<p>Luck has failed you! You threw away two pair only to get beat by a lower two pair then what you were holding at the start. The cowboys have taken the lead. Another loss like this will bring this game to a close.  The next deal leaves you with A, A, K, Q, J.</p>
<p>You decide to </p>
<ul>
  <li><a href="d51.html">Hold onto the Ace pair and try for three of a kind.</a></li>
  <li><a href="d52.html">Discard an Ace and try for a straight.</a></li>
</ul>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char d42_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Dinosaurs</h1>
<p>It worked! You drew a full house.  You won the hand and the game!</p>
<p>The cowboys leave in defeat to be exiled from this land.</p>
<h2>DINOSAURS ARE VICTORIOUS</h2>
<h2>YOU WIN!</h2>
<p></p>
<br>
<p><a href="/">Play Again</a></p>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char d43_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Dinosaurs</h1>
<p>The bluff failed!  What were you thinking trying to bluff them at their own game?  You lost the hand.  Another loss like this will bring this game to a close.  The next deal leaves you with A, A, K, Q, J.</p>
<p>You decide to </p>
<ul>
  <li><a href="d51.html">Hold onto the Ace pair and try for three of a kind.</a></li>
  <li><a href="d52.html">Discard an Ace and try for a straight.</a></li>
</ul>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char d44_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Dinosaurs</h1>
<p>Luck has failed you! You threw away two pair only to get beat by a lower two pair then what you were holding at the start. The cowboys have won the hand and the game! You will be forced into exile leaving this land to be ruled by the cowboys.</p>
<h2>YOU HAVE LOST</h2>
<h2>GAME OVER</h2>
<p></p>
<br>
<p><a href="/">Try Again</a></p>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char d45_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Dinosaurs</h1>
<p>It worked! You drew a full house. You won the hand.  It’s a close game and the bets are high enough now that one hand can win or lose the whole thing.  The next deal leaves you with A, A, K, Q, J.</p>
<p>You decide to </p>
<ul>
  <li><a href="d51.html">Hold onto the Ace pair and try for three of a kind.</a></li>
  <li><a href="d52.html">Discard an Ace and try for a straight.</a></li>
</ul>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char d46_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Dinosaurs</h1>
<p>The bluff failed!  What were you thinking trying to bluff them at their own game?  The cowboys have won the hand and the game! You will be forced into exile leaving this land to be ruled by the cowboys.</p>
<h2>YOU HAVE LOST</h2>
<h2>GAME OVER</h2>
<p></p>
<br>
<p><a href="/">Try Again</a></p>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char d51_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Dinosaurs</h1>
<p>You got your third Ace and fourth one to boot!  The cowboy’s flush was no match for your four of a kind.  You won the hand and the game!  The cowboys leave in defeat to be exiled from this land.</p>
<h2>DINOSAURS ARE VICTORIOUS</h2>
<h2>YOU WIN!</h2>
<p></p>
<br>
<p><a href="/">Play Again</a></p>
<p></p>
<br>
</body>
</html>
)rawliteral";

const char d52_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Dinosaurs</h1>
<p>You threw away a good pair only to be left with nothing but a high card.  This was for all the marbles, and you came up short. The cowboys have won the hand and the game! You will be forced into exile leaving this land to be ruled by the cowboys.</p>
<h2>YOU HAVE LOST</h2>
<h2>GAME OVER</h2>
<p></p>
<br>
<p><a href="/">Try Again</a></p>
<p></p>
<br>
</body>
</html>
)rawliteral";

// reboot.html base upon https://gist.github.com/Joel-James/62d98e8cb3a1b6b05102
const char reboot_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h3>
  Rebooting, returning to main page in <span id="countdown">30</span> seconds
</h3>
<script type="text/javascript">
  var seconds = 20;
  function countdown() {
    seconds = seconds - 1;
    if (seconds < 0) {
      window.location = "/";
    } else {
      document.getElementById("countdown").innerHTML = seconds;
      window.setTimeout("countdown()", 1000);
    }
  }
  countdown();
</script>
</body>
</html>
)rawliteral";
