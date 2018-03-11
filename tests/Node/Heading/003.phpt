--TEST--
CommonMark\Node\Heading Level Error
--FILE--
<?php
$heading = new CommonMark\Node\Heading;

try {
	$heading->setHeadingLevel([]);
} catch (InvalidArgumentException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
