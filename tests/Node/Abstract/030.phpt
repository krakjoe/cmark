--TEST--
CommonMark\Node debug
--FILE--
<?php
$doc = new CommonMark\Node\Document;

$para = new CommonMark\Node\Paragraph;

$doc->appendChild($para);

var_dump($doc);

$para->unlink();

var_dump($doc);

$doc->appendChild($para);

var_dump($doc);
?>
--EXPECT--
object(CommonMark\Node\Document)#1 (1) {
  ["children"]=>
  array(1) {
    [0]=>
    object(CommonMark\Node\Paragraph)#2 (0) {
    }
  }
}
object(CommonMark\Node\Document)#1 (0) {
}
object(CommonMark\Node\Document)#1 (1) {
  ["children"]=>
  array(1) {
    [0]=>
    object(CommonMark\Node\Paragraph)#2 (0) {
    }
  }
}
