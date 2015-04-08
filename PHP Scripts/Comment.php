<?php


class  Comment
{
    var $Id;
    var $Writer;
    var $Melody;
    var $Script;
    var $Date;
    var $Key_Id;
    var $Key_Writer;
    var $Key_Melody;
    var $Key_Script;
    var $Key_Date;
    var $Converter;

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
      $this->Converter=new Bridge("Comment");
      $this->setKeys();
    }

    function setKeys()
    {
      $this->Key_Id=$this->Converter->Attributes[0];
      $this->Key_Writer=$this->Converter->Attributes[1];
      $this->Key_Melody=$this->Converter->Attributes[2];
      $this->Key_Script=$this->Converter->Attributes[3];
      $this->Key_Date=$this->Converter->Attributes[4];
    }

    function setId($par)
    {
      $this->Id=$par;
    }

    function setWriter($par)
    {
       $this->Writer = $par;
    }

    function setMelody($par)
    {
       $this->Melody = $par;
    }

    function setScript($par)
    {
       $this->Script = $par;
    }

    function setDate($par)
    {
      $this->Date=date("Y-m-d",strtotime($par));
    }

    function getId()
    {
      return $this->Id;
    }

    function getWriter()
    {
       return $this->Writer;
    }

    function getMelody()
    {
       return $this->Melody;
    }

    function getScript()
    {
       return $this->Script;
    }

    function getDate()
    {
      return $this->Date;
    }

    function setComment($Result)
    {
        $this->Id=$Result[$this->Key_Id];
        $this->Writer=$Result[$this->Key_Writer];
        $this->Melody=$Result[$this->Key_Melody];
        $this->Script=$Result[$this->Key_Script];
        $this->Date=$Result[$this->Key_Date];
    }

    function select()
    {
      $Keys = array($this->Key_Id);
      $Values = array($this->Id);
      $Results=$this->Converter->select($Keys,$Values);
      $i=0;
      while ($i<count($Results)) 
      {
        $this->setComment($Results[$i]);
        $i=$i+1;
      }
    }

    function setParameters()
    {
      $Keys[0]=$this->Key_Writer;
      $Keys[1]=$this->Key_Melody;
      $Keys[2]=$this->Key_Script;
      $Keys[3]=$this->Key_Date;
      return $Keys;
    }

    function insert()
    {
      $Values = array("'$this->Writer'","'$this->Melody'","'$this->Script'","'$this->Date'");
      $this->Id = $this->Converter->insert($this->setParameters(),$Values);
    }

    function update()
    {
      $Values = array("'$this->Writer'","'$this->Melody'","'$this->Script'","'$this->Date'");
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
      echo "Writer : " . $this->Writer . "<br/>";
      echo "Melody : " . $this->Melody . "<br/>";
      echo "Comment : " . $this->Script . "<br/>";
      echo "Date : " . $this->Date . "<br/>";
    }

}
?>