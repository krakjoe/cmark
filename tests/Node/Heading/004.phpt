--TEST--
CommonMark\Node\Heading Level Error
--FILE--
<?php
$heading = new CommonMark\Node\Heading;

try {
	$heading->setHeadingLevel(42);
} catch (RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
