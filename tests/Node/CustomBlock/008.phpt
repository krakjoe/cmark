--TEST--
CommonMark\Node\CustomBlock clone
--FILE--
<?php
$doc = new CommonMark\Node\Document;

$node = new CommonMark\Node\CustomBlock;
$node->setOnEnter("ENTER");
$node->setOnLeave("LEAVE");
$node->appendChild(
	new CommonMark\Node\Text("NODE"));

$doc->appendChild($node);

var_dump($doc, clone $doc);
?>
--EXPECT--
object(CommonMark\Node\Document)#1 (1) {
  ["children"]=>
  array(1) {
    [0]=>
    object(CommonMark\Node\CustomBlock)#2 (3) {
      ["enter"]=>
      string(5) "ENTER"
      ["leave"]=>
      string(5) "LEAVE"
      ["children"]=>
      array(1) {
        [0]=>
        object(CommonMark\Node\Text)#3 (1) {
          ["literal"]=>
          string(4) "NODE"
        }
      }
    }
  }
}
object(CommonMark\Node\Document)#4 (1) {
  ["children"]=>
  array(1) {
    [0]=>
    object(CommonMark\Node\CustomBlock)#5 (3) {
      ["enter"]=>
      string(5) "ENTER"
      ["leave"]=>
      string(5) "LEAVE"
      ["children"]=>
      array(1) {
        [0]=>
        object(CommonMark\Node\Text)#6 (1) {
          ["literal"]=>
          string(4) "NODE"
        }
      }
    }
  }
}
