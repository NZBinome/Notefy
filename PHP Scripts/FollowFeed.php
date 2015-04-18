<?php


class FollowFeed 
{
	var $Date;
	var $Type;
	var $Follower;
	var $Followed;


	function __construct() 
    { 
        $a = func_get_args(); 
        $i = func_num_args(); 
        if (method_exists($this,$f='__construct'.$i)) { 
            call_user_func_array(array($this,$f),$a); 
        } 
    }

	function __construct4($FollowerId,$FollowedId,$type,$Time)
	{
		$this->Follower = new User($FollowerId);
		$this->Followed = new User($FollowedId);
		$this->Type = $type;
		$this->Date = $Time;
	}


	function toXML()
	{
		$ToSend = "<$this->Type>";
		$ToSend = $ToSend ."<Date> $this->Date </Date>";
		$ToSend = $ToSend . "<Follower>";
		$ToSend = $ToSend . $this->Follower->toXML();
		$ToSend = $ToSend . "</Follower><Followed>";
		$ToSend = $ToSend . $this->Followed->toXML();
		$ToSend = $ToSend . "</Followed>";
		$ToSend = $ToSend . "</$this->Type>";
		return $ToSend;
	}
}

?>