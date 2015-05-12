<?php

include 'User.php';
include 'Melody.php';
include 'Bridge.php';
include 'Toolkit.php';
include 'Share.php';
include 'Follows.php';
include 'Comment.php';
include 'Applause.php';
include 'ApplauseFeed.php';
include 'CommentFeed.php';
include 'ShareFeed.php';
include 'CreateFeed.php';
include 'FollowFeed.php';


$UserId = $_GET['UserId'];


$Toolkit1 = new Toolkit();

$Followed =  $Toolkit1->getFollowed($UserId);


$i = 0;
$k = 0;

while ($i<count($Followed)) 
{
	$Users[$i] = new User($Followed[$i]->getFollowed());

	$j = 0;
	$Melodies = $Toolkit1->getMelodiesOfUser($Users[$i]->getId());
	while ($j <count($Melodies)) 
	{
		$Feeds[$k] = new CreateFeed($Users[$i]->getId(),$Melodies[$j]->getId(),"Create",$Melodies[$j]->getDate());
		$Dates[$k] = $Melodies[$j]->getDate();
		$j =$j+1;
		$k=$k+1;
	}


	$j = 0;
	$Shares = $Toolkit1->getSharedMelodies($Users[$i]->getId());
	while ($j <count($Shares)) 
	{
		$Melody = new Melody($Shares[$j]->getMelody());
		$Original = new User($Melody->getUser_Id());
		$Feeds[$k] = new ShareFeed($Users[$i]->getId(),$Melody->getId(),$Original->getId(),"Share",$Shares[$j]->getDate());
		$Dates[$k] = $Shares[$j]->getDate();
		$j =$j+1;
		$k=$k+1;
	}


	$j = 0;
	$Comments = $Toolkit1->getCommentsOfUser($Users[$i]->getId());
	while ($j <count($Comments)) 
	{
		$Melody = new Melody($Comments[$j]->getMelody());
		$Feeds[$k] = new CommentFeed($Users[$i]->getId(),$Melody->getId(),"Comment",$Comments[$j]->getDate(),$Comments[$j]->getScript());
		$Dates[$k] = $Comments[$j]->getDate();
		$j =$j+1;
		$k=$k+1;
	}


	$j = 0;
	$Applause = $Toolkit1->getApplauseofUser($Users[$i]->getId());

	while ($j <count($Applause)) 
	{
		$Melody = new Melody($Applause[$j]->getMelody());
		$Feeds[$k] = new ApplauseFeed($Users[$i]->getId(),$Melody->getId(),"Applause",$Applause[$j]->getDate());
		$Dates[$k] = $Applause[$j]->getDate();
		$j =$j+1;
		$k=$k+1;
	}


	$j = 0;
	$Follows = $Toolkit1->getFollowed($Users[$i]->getId());

	while ($j <count($Follows)) 
	{
		$FollowedUser = new User($Follows[$j]->getFollowed());
		$Feeds[$k] = new FollowFeed($Users[$i]->getId(),$FollowedUser->getId(),"Follow",$Follows[$j]->getDate());
		$Dates[$k] = $Follows[$j]->getDate();
		$j =$j+1;
		$k=$k+1;
	}

	$i = $i + 1;
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