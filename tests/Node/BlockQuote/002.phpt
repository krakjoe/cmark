--TEST--
CommonMark\Node fetch BlockQuote
--FILE--
<?php
$md = <<<MD
> block quote
MD;

$parser = new CommonMark\Parser();

$parser->parse($md);

$doc = $parser->finish();

if ($doc->firstChild instanceof CommonMark\Node\BlockQuote) {
	echo "OK";
}
?>
--EXPECT--
OK
