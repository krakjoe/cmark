--TEST--
CommonMark\Node Insert After Error
--FILE--
<?php
$document = new CommonMark\Node\Document;

try {
	$document->insertAfter([]);
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
