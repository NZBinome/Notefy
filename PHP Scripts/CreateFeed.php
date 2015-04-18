<?php


class CreateFeed 
{
	var $Date;
	var $Type;
	var $User;
	var $Melody;


	function __construct() 
    { 
        $a = func_get_args(); 
        $i = func_num_args(); 
        if (method_exists($this,$f='__construct'.$i)) { 
            call_user_func_array(array($this,$f),$a); 
        } 
    }

	function __construct4($UserId,$MelodyId,$type,$Time)
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