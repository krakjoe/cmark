--TEST--
CommonMark\Node fetch ThematicBreak
--FILE--
<?php
$md = <<<MD
***
MD;

$parser = new CommonMark\Parser();

$parser->parse($md);

$doc = $parser->finish();

if ($doc->firstChild instanceof CommonMark\Node\ThematicBreak) {
	echo "OK";
}
?>
--EXPECT--
OK
