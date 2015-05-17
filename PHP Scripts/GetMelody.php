<?php
include 'Melody.php';
include 'Bridge.php';
include 'User.php';
include 'Toolkit.php';
include 'Follows.php';


$MelodyId = $_GET['MelodyId'];

$Melody = new Melody($MelodyId);
$User = new User($Melody->getUser_Id());
$Toolkit1 = new Toolkit();

$ApplauseCount = $Toolkit1->getApplauseCount($Melody->getId());
$ShareCount = $Toolkit1->getShareCount($Melody->getId());
$CommentCount = $Toolkit1->getCommentCount($Melody->getId());

$ToSend = "<Root>";
$ToSend = $ToSend . "<Header>";
$ToSend = $ToSend . $Melody->toXML();
$ToSend = $ToSend . $User->toXML();
$ToSend = $ToSend . "<ApplauseCount>" . $ApplauseCount . "</ApplauseCount>";
$ToSend = $ToSend . "<ShareCount>" . $ShareCount . "</ShareCount>";
$ToSend = $ToSend . "<CommentCount>" . $CommentCount . "</CommentCount>";
$ToSend = $ToSend . "</Header>";
$ToSend = $ToSend . "</Root>";


		

echo $ToSend;

?>