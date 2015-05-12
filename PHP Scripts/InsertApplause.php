<?php

include 'Bridge.php';
include 'Applause.php';

$UserId = $_GET['UserId'];
$MelodyId = $_GET['MelodyId'];

$Applause1 = new Applause();
$Applause1->setSpectator($UserId);
$Applause1->setMelody($MelodyId);
date_default_timezone_set("Asia/Beirut");
$Applause1->setDate(date("Y-m-d H:i:s"));
$Applause1->insert();

?>