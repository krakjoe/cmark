--TEST--
CommonMark\Node Traversable Error
--FILE--
<?php
$doc = new CommonMark\Node\Document;

try {
	foreach ($doc as $ev => &$node) {}
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
