--TEST--
CommonMark\Node\Text Literals
--FILE--
<?php
$text = new CommonMark\Node\Text;

$text->setLiteral("OK");

echo $text->getLiteral();
?>
--EXPECT--
OK
