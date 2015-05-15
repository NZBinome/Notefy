<?php

include 'Melody.php';
include 'Bridge.php';

$UserId = $_GET['UserId'];
$MelodyName= $_GET['MelodyName'];

$Melody1 = new Melody();
$Melody1->setTitle($MelodyName);
$Melody1->setFile_Link("Melodies/" . $UserId . "/" . $MelodyName);
date_default_timezone_set("Asia/Beirut");
$Melody1->setDate(date("Y-m-d H:i:s"));
$Melody1->setUser_Id($UserId);
//$Melody1->display();
$Melody1->insert();

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