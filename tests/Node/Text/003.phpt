--TEST--
CommonMark\Node\Text Literals Errors
--FILE--
<?php
$text = new CommonMark\Node\Text;

try {
	$text->setLiteral([]);
} catch (InvalidArgumentException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
