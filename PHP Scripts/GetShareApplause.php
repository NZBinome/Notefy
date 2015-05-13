<?php

include 'Bridge.php';
include 'Applause.php';
include 'Share.php';

$UserId = $_GET['UserId'];
$MelodyId = $_GET['MelodyId'];

$Applause1 = new Applause($UserId,$MelodyId);
$Share1 = new Share($UserId,$MelodyId);

$ToSend = "<Root>" ;
$ToSend = $ToSend . $Applause1->toXML();
$ToSend = $ToSend . $Share1->toXML();
$ToSend = $ToSend . "</Root>";
echo $ToSend;
?>