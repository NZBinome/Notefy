<?php
include 'Melody.php';
include 'Bridge.php';
include 'User.php';

$MelodyId = $_GET['MelodyId'];

$Melody = new Melody($MelodyId);
$User = new User($Melody->getUser_Id());

$ToSend = "<Root>";
$ToSend = $ToSend . "<Header>";
$ToSend = $ToSend . $Melody->toXML();
$ToSend = $ToSend . $User->toXML();
$ToSend = $ToSend . "</Header>";
$ToSend = $ToSend . "</Root>";

echo $ToSend;

?>