<?php


class Feed 
{
	var $Date;
	var $Type;
	var $User;
	var $Melody;
	
	function __construct($UserId,$MelodyId,$type,$Time)
	{
		$this->User = new User($UserId);
		$this->Melody = new Melody ($MelodyId);
		$this->Type = $type;
		$this->Date = $Time;
	}

	function toXML()
	{
		$ToSend = "<$this->Type>";
		$ToSend = $ToSend ."<Date> $this->Date </Date>";
		$ToSend = $ToSend . $this->User->toXML();
		$ToSend = $ToSend . $this->Melody->toXML();
		$ToSend = $ToSend . "</$this->Type>";
		return $ToSend;

	}
}

?>