--TEST--
CommonMark\Node Insert After Error
--FILE--
<?php
$document = new CommonMark\Node\Document;

try {
	$document->insertAfter([]);
} catch (InvalidArgumentException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
