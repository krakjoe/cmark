--TEST--
CommonMark\Node Insert Before Error
--FILE--
<?php
$document = new CommonMark\Node\Document;

try {
	$document->insertBefore([]);
} catch (InvalidArgumentException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
