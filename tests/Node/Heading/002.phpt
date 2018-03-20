--TEST--
CommonMark\Node\Heading Level
--FILE--
<?php
$heading = new CommonMark\Node\Heading;
$heading->level = 3;

echo $heading->level;
?>
--EXPECT--
3
