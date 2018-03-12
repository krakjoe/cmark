--TEST--
CommonMark\Node\Text Literals Construct
--FILE--
<?php
$text = new CommonMark\Node\Text("OK");

echo $text->getLiteral();
?>
--EXPECT--
OK
