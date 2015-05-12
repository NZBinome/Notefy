<?php

include 'User.php';
include 'Melody.php';
include 'Bridge.php';
include 'Toolkit.php';
include 'CommentFeed.php';
include 'Comment.php';

$MelodyId = $_GET['MelodyId'];

$Toolkit1 = new Toolkit();

$Comments = $Toolkit1->getComments($MelodyId);

$i = 0;

while ($i<count($Comments)) 
{
	$User = new User($Comments[$i]->getWriter());
	$Melody = new Melody($Comments[$i]->getMelody());
	$Feeds[$i] = new CommentFeed($Comments[$i]->getWriter(),$Comments[$i]->getMelody(),"Comment",$Comments[$i]->getDate(),$Comments[$i]->getScript());
	$Dates[$i] = $Comments[$i]->getDate();
	$i=$i+1;
}

array_multisort($Dates, $Feeds);

$i=0;
$ToSend = "<Root>";

while ($i<count($Feeds)) {
	$ToSend = $ToSend . $Feeds[$i]->toXML();
	$i=$i+1;
}

$ToSend = $ToSend . "</Root>";

echo "$ToSend";

?>