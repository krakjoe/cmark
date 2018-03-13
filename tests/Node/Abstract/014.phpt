--TEST--
CommonMark\Node Insert Before Error
--FILE--
<?php
$document = new CommonMark\Node\Document;

try {
	$document->insertBefore([]);
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
