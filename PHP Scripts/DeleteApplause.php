<?php

include 'Bridge.php';
include 'Applause.php';

$UserId = $_GET['UserId'];
$MelodyId = $_GET['MelodyId'];

$Applause1 = new Applause($UserId,$MelodyId);
$Applause1->delete();

?>