<?php

include 'Melody.php';
include 'Bridge.php';

$UserId = $_GET['UserId'];
$MelodyName= $_GET['MelodyName'];

$arguments = "";

$file = fopen("Melodies/" . $UserId . "/" . $MelodyName . "/Readme.txt","r");

while(! feof($file))
  {
  	$string = trim (fgets($file));
  	if (feof(($file))) 
  	{
  		break;
  	}
  	$arguments = $arguments . "\"Melodies/" . $UserId . "/" . $MelodyName . "/" . $string . "\" ";
  }

fclose($file);


exec('./Mixer -i '. $arguments  . '-o "Melodies/' . $UserId . '/' . $MelodyName . '/Melody.aif" -c /usr/local/bin/fluidsynth -s SoundFonts/gm_soundfonts.sf2 & &> /dev/null &');

?>