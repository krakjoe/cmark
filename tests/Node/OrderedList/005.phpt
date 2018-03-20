--TEST--
CommonMark\Node fetch OrderedList
--FILE--
<?php
$md = <<<MD
  1) item
  2) item
MD;

$parser = new CommonMark\Parser();

$parser->parse($md);

$doc = $parser->finish();

if ($doc->firstChild instanceof CommonMark\Node\OrderedList) {
	echo "OK";
}
?>
--EXPECT--
OK
