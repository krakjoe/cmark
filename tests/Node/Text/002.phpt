--TEST--
CommonMark\Node\Text Literals
--FILE--
<?php
$text = new CommonMark\Node\Text;

$text->literal = "OK";

echo $text->literal;
?>
--EXPECT--
OK
