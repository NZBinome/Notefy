<?php

include 'Bridge.php';
include 'Share.php';

$UserId = $_GET['UserId'];
$MelodyId = $_GET['MelodyId'];

$Share1 = new Share();
$Share1->setSharer($UserId);
$Share1->setMelody($MelodyId);
date_default_timezone_set("Asia/Beirut");
$Share1->setDate(date("Y-m-d H:i:s"));
$Share1->insert();

?>