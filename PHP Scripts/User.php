<?php


class  User
{
    var $Id;
    var $Last_Name;
    var $First_Name;
    var $Stage_Name;
    var $Birthday;
    var $Picture_Link;
    var $Key_Id;
    var $Key_Last_Name;
    var $Key_First_Name;
    var $Key_Stage_Name;
    var $Key_Birthday;
    var $Key_Picture_Link;
    var $Converter;
    var $Map;


    function __construct() 
    { 
        $a = func_get_args(); 
        $i = func_num_args(); 
        if (method_exists($this,$f='__construct'.$i)) { 
            call_user_func_array(array($this,$f),$a); 
        } 
    }

    function __construct1($Id)
    {
      $this->__construct0();
      $this->Id=$Id;
      $this->select();
    }

    function __construct0()
    {
      $this->Converter=new Bridge("Users");
      $this->setKeys();
    }

    function setKeys()
    {
      $this->Key_Id=$this->Converter->Attributes[0];
      $this->Key_First_Name=$this->Converter->Attributes[1];
      $this->Key_Last_Name=$this->Converter->Attributes[2];
      $this->Key_Stage_Name=$this->Converter->Attributes[3];
      $this->Key_Picture_Link=$this->Converter->Attributes[4];
      $this->Key_Birthday=$this->Converter->Attributes[5];
    }

    function setId($par)
    {
      $this->Id=$par;
    }

    function setFirst_Name($par)
    {
       $this->First_Name = $par;
    }

    function setLast_Name($par)
    {
       $this->Last_Name = $par;
    }

    function setStage_Name($par)
    {
       $this->Stage_Name = $par;
    }

    function setBirthday($par)
    {
      $this->Birthday=date("Y-m-d",strtotime($par));
    }

    function setPicture_Link($par)
    {
      $this->Picture_Link=$par;
    }

    function getId()
    {
      return $this->Id;
    }

    function getFirst_Name()
    {
       return $this->First_Name;
    }

    function getLast_Name()
    {
       return $this->Last_Name;
    }

    function getStage_Name()
    {
       return $this->Stage_Name;
    }

    function getBirthday()
    {
      return $this->Birthday;
    }

    function getPicture_Link()
    {
      return $this->Picture_Link;
    }

    function setUser($Result)
    {       
        $this->Id=$Result[$this->Key_Id];
        $this->First_Name=$Result[$this->Key_First_Name];
        $this->Last_Name=$Result[$this->Key_Last_Name];
        $this->Stage_Name=$Result[$this->Key_Stage_Name];
        $this->Picture_Link=$Result[$this->Key_Picture_Link];
        $this->Birthday=$Result[$this->Key_Birthday];

        $Toolkit1 = new Toolkit();
        $Fans = $Toolkit1->getFollowers($this->Id);
        $this->FanCount = count($Fans);
    }

    function select()
    {
      $Keys = array($this->Key_Id);
      $Values = array($this->Id);
      $Results=$this->Converter->select($Keys,$Values);
      $this->setUser($Results[0]);
      $i=1;
      while ($i<count($Results)) 
      {
        $this->setUser($Results[$i]);
        $i=$i+1;
      }
    }

    function selectByStageName($Stage_Name)
    {
      $Keys = array($this->Key_Stage_Name); 
      $Values = array($Stage_Name);
      $Results=$this->Converter->select($Keys,$Values);
      $this->setUser($Results[0]);
    }

    function setParameters()
    {
      $Keys[0]=$this->Key_First_Name;
      $Keys[1]=$this->Key_Last_Name;
      $Keys[2]=$this->Key_Stage_Name;
      $Keys[3]=$this->Key_Picture_Link;
      $Keys[4]=$this->Key_Birthday;
      return $Keys;
    }

    function insert()
    {
      $Values = array("'$this->First_Name'","'$this->Last_Name'","'$this->Stage_Name'","'$this->Picture_Link'","'$this->Birthday'");
      $this->Id = $this->Converter->insert($this->setParameters(),$Values);
    }

    function update()
    {
      $Values = array("'$this->First_Name'","'$this->Last_Name'","'$this->Stage_Name'","'$this->Picture_Link'","'$this->Birthday'");
      $ParaKeys=array($this->Key_Id);
      $ParaValues=array("$this->Id");
      $this->Converter->update($this->setParameters(),$Values,$ParaKeys,$ParaValues);
    }

    function delete()
    {
      $Keys = array($this->Key_Id);
      $Values = array($this->Id);
      $this->Converter->delete($Keys,$Values);
    }

    function display()
    {
      echo "User <br/>";
      echo "Id : " . $this->Id . "<br/>";
      echo "Last_Name : " . $this->Last_Name . "<br/>";
      echo "First_Name : " . $this->First_Name . "<br/>";
      echo "Stage_Name : " . $this->Stage_Name . "<br/>";
      echo "Birthday : " . $this->Birthday . "<br/>";
      echo "Picture_Link : " . $this->Picture_Link . "<br/>";
      echo "FanCount : ". $this->FanCount . "<br/>";
    }

    function toXML()
    {
      $echo = "<User>";
      $echo = $echo . "<Id>" . $this->Id . "</Id>";
      $echo = $echo . "<Last_Name>" . $this->Last_Name . "</Last_Name>";
      $echo = $echo . "<First_Name>" . $this->First_Name . "</First_Name>";
      $echo = $echo . "<Stage_Name>" . $this->Stage_Name . "</Stage_Name>";
      $echo = $echo . "<Birthday>" . $this->Birthday . "</Birthday>";
      $echo = $echo . "<Picture_Link>" . $this->Picture_Link . "</Picture_Link>";
      $echo = $echo . "<FanCount>" . $this->FanCount . "</FanCount>";
      $echo = $echo . "</User>";
      return $echo ;
    }

}
?>