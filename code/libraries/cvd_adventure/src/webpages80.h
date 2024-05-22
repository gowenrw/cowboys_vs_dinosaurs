const char notes_txt80[] PROGMEM = R"rawliteral(
  I setup the B2TF server but its in a basic state. Need to improve the authentication and configuration.

web server: port 1985
user: mcfly
password: N0tAchicken

)rawliteral";

const char index_html80[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html lang="en">
<head>
  <meta charset="UTF-8">
</head>
<body>
<h1>Welcome to the Dallas Hackers (DC214) Future Badge</h1>
<p>You have found the Future Badge CTF for Defcon 31<p/>
<p>We’re glad you’re here. We need more people like you. This is meant to be fun and progressively challenging. We hope you enjoy it.</p>
<p>"Wait a minute. Wait a minute Doc, uh, are you telling me you built a time machine … out of a DeLorean?”<br/>
<i>--Marty McFly</i></p>

<img alt="Time Machine Clock Circuits" 
src='data:image/jpeg;base64,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
' />

<p>The Badge Contains the following Flags:
<ul>
<li>3 Cryptographic challenges</li>
<li>7 CTF challenges</li>
</ul>
</p>
<h2>Challenge Types &amp; Tools</h2>
<h3>Cryptography:</h3>
<p>In Cryptography, the goal is to seek flags by cracking or clone cryptographic objects or algorithms. Below are useful tools I have found in CTFs:</p>
<p>CyberChef - An online/offline Cyber Swiss Army Knife - a web app for encryption, encoding, compression and data<br>
dCode - dCode is a toolkit website for decryption, ciphering, mathematics, numeration, etc.<br>
FeatherDuster - An automated, modular cryptanalysis tool<br>
Hash Extender - A utility tool for performing hash length extension attacks<br>
RSATool - Generate private key with knowledge of p and q<br>
XORTool - A tool to analyze multi-byte xor cipher</p>
<h3>Steganography</h3>
<p>Steganography usually involves finding the hints or flags that have been hidden with steganography. Most commonly a media file will be given as a task with no further instructions, and the participants have to be able to uncover the message that has been encoded in the media.</p>
<p>Steghide - Hide data in various kind of images<br>
Stegsolve - Apply various steganography techniques to images<br>
Zsteg - PNG/BMP analysis<br>
Exiftool - Read and write meta information in files<br>
Pngtools - For various analysis related to PNGs</p>
<h3>Web</h3>
<p>Web challenges in involve the use of HTTP, and similar protocols, to transfer and display information over the internet.</p>
<p>BurpSuite - A graphical tool to testing website security.<br>
Postman - Add on for chrome for debugging network requests<br>
Raccoon - A high-performance offensive security tool for reconnaissance and vulnerability scanning<br>
SQLMap - Automatic SQL injection and database takeover tooli<br>
W3af - Web Application Attack and Audit Framework.</p>
<h3>Forensics</h3>
<p>Forensics include file format analysis, steganography, memory dump analysis, or network packet capture analysis</p>
<p>Audacity - Analyze sound files (mp3, m4a, whatever)<br>
Bkhive and Samdump2 - Dump SYSTEM and SAM files<br>
CFF Explorer - PE Editor<br>
Creddump - Dump windows credentials<br>
Foremost - Extract particular kind of files using headers<br>
NetworkMiner - Network Forensic Analysis Tool<br>
Nmap - Network Mapper<br>
Shellbags - Investigate NT_USER.dat files<br>
UsbForensics - Contains many tools for USB forensics<br>
Volatility - To investigate memory dumps</p>
<h3>Reverse engineering</h3>
<p>Reverse Engineering is typically the process of taking a compiled program and converting it into a "human-readable" format.</p>
<p>ApkTool - Android Decompiler<br>
Barf - Binary Analysis and Reverse engineering Framework<br>
Binary Ninja - Binary analysis framework<br>
BinWalk - Analyze, reverse engineer, and extract firmware images.<br>
Boomerang - Decompile x86 binaries to C<br>
Frida - Dynamic Code Injection<br>
GDB - The GNU project debugger<br>
GEF - GDB plugin<br>
IDA Pro - Most used Reversing software<br>
Jadx - Decompile Android files</p>
<p>Many challenges in CTFs will be completely random and unprecedented, requiring simply logic, knowledge, and patience to be solved. There is no sure-fire way to prepare for these, but as you complete more CTFs you will be able to recognize and hopefully have more clues on how to solve them.</p>
<p>Best of Luck from the Dallas Hackers (DC214) Badge Team<br/>
<ul>
<li>@alt_bier</li>
<li>@Sapient</li>
</ul>
</p>
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
